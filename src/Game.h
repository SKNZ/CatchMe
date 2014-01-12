/**
 * @file   Game.h
 *
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Main game file header, contains game modes, tokens (+ enum), controls, and main function.
 *
 **/
#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <chrono>

#include "GameMode.h"
#include "GameModes/Classic1v1.h"
#include "GameModes/Classic1v1v1.h"
#include "GameModes/Classic1v1v1v1.h"
#include "GameModes/Classic2v2.h"
#include "GameModes/Classic3v1.h"
#include "GameModes/Survivor1v1.h"
#include "GameModes/Survivor1v1v1.h"
#include "GameModes/Survivor1v1v1v1.h"
#include "GameModes/Survivor2v2.h"
#include "GameModes/Survivor3v1.h"
#include "GameModes/MapEditor.h"

#include "Menu.h"

/**
 * 
 * @namespace nsGame
 * 
 * @brief Namespace containing everything related to main game logic.
 * 
 **/
namespace nsGame
{
    /**
    *
    * @brief All the game modes.
    *
    **/
    const std::vector<SGameMode> KGameModes =
    {
        MakeGameMode ("Classic 1v1", 2, 1, false, nsClassic1v1::GetSize, nsClassic1v1::MovePlayer, nsClassic1v1::InitializeRound, nsClassic1v1::BuildMatrix, nsClassic1v1::ValidatePlayerPositions, nsClassic1v1::IsGameOver, nsMenu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 1v1v1", 3, 1, false, nsClassic1v1v1::GetSize, nsClassic1v1v1::MovePlayer, nsClassic1v1v1::InitializeRound, nsClassic1v1v1::BuildMatrix, nsClassic1v1v1::ValidatePlayerPositions, nsClassic1v1v1::IsGameOver, nsMenu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 1v1v1v1", 4, 1, false, nsClassic1v1v1v1::GetSize, nsClassic1v1v1v1::MovePlayer, nsClassic1v1v1v1::InitializeRound, nsClassic1v1v1v1::BuildMatrix, nsClassic1v1v1v1::ValidatePlayerPositions, nsClassic1v1v1v1::IsGameOver, nsMenu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 2v2", 4, 1, false, nsClassic2v2::GetSize, nsClassic2v2::MovePlayer, nsClassic2v2::InitializeRound, nsClassic2v2::BuildMatrix, nsClassic2v2::ValidatePlayerPositions, nsClassic2v2::IsGameOver, nsSurvivor2v2::ShowWinScreen),
        MakeGameMode ("Classic 3v1", 4, 4, false, nsClassic3v1::GetSize, nsClassic3v1::MovePlayer, nsClassic3v1::InitializeRound, nsClassic3v1::BuildMatrix, nsClassic3v1::ValidatePlayerPositions, nsClassic3v1::IsGameOver, nsClassic3v1::ShowWinScreen),

        MakeGameMode ("Survivor 1v1", 2, 1, false, nsSurvivor1v1::GetSize, nsSurvivor1v1::MovePlayer, nsSurvivor1v1::InitializeRound, nsSurvivor1v1::BuildMatrix, nsSurvivor1v1::ValidatePlayerPositions, nsSurvivor1v1::IsGameOver, nsMenu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 1v1v1", 3, 1, false, nsSurvivor1v1v1::GetSize, nsSurvivor1v1v1::MovePlayer, nsSurvivor1v1v1::InitializeRound, nsSurvivor1v1v1::BuildMatrix, nsSurvivor1v1v1::ValidatePlayerPositions, nsSurvivor1v1v1::IsGameOver, nsMenu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 1v1v1v1", 4, 1, false, nsSurvivor1v1v1v1::GetSize, nsSurvivor1v1v1v1::MovePlayer, nsSurvivor1v1v1v1::InitializeRound, nsSurvivor1v1v1v1::BuildMatrix, nsSurvivor1v1v1v1::ValidatePlayerPositions, nsSurvivor1v1v1v1::IsGameOver, nsMenu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 2v2", 4, 1, false, nsSurvivor2v2::GetSize, nsSurvivor2v2::MovePlayer, nsSurvivor2v2::InitializeRound, nsSurvivor2v2::BuildMatrix, nsSurvivor2v2::ValidatePlayerPositions, nsSurvivor2v2::IsGameOver, nsSurvivor2v2::ShowWinScreen),
        MakeGameMode ("Survivor 3v1", 4, 4, false, nsSurvivor3v1::GetSize, nsSurvivor3v1::MovePlayer, nsSurvivor3v1::InitializeRound, nsSurvivor3v1::BuildMatrix, nsSurvivor3v1::ValidatePlayerPositions, nsSurvivor3v1::IsGameOver, nsSurvivor3v1::ShowWinScreen),
        
        MakeGameMode ("Tools Map Editor", 1, 1, true, nsMapEditor::GetSize, nsMapEditor::MovePlayer, nsMapEditor::InitializeRound, nsMapEditor::BuildMatrix, nsMapEditor::ValidatePlayerPositions, nsMapEditor::IsGameOver, nsMapEditor::ShowWinScreen)
    }; // KGamesModes initializer list

    /**
    *
    * @brief An id for each token
    *
    **/
    enum TokenIds
    {
        KTokenPlayer1,
        KTokenPlayer2,
        KTokenPlayer3,
        KTokenPlayer4,
        KTokenObstacle,
        KTokenEmpty
    }; // TokenIds

    /**
    *
    * @brief List of all the possible tokens.
    *
    * A token is an item that occupies a case on the grid, such as nothing, a player, or an obstacle.
    * These, however, do not include the borders.
    * The last token is the empty token.
    *
    **/
    const std::vector<char> KTokens =
    {
        'X',
        'O',
        '#',
        '@',
        '|',
        ' '
    }; // KTokens initializer list

    /**
    *
    * @brief Associates each (player) token with a list of controls
    *
    * Every player token has its own set of controls, composed of 9 keyboard keys, which should form a square.
    * 0 -> Upleft, 1 -> Up, 2 -> Upright
    * 3 -> Left, 4 -> Stay (disabled), 5 -> Right
    * 6 -> Downleft, 7 -> Down, 8 -> Downright
    *
    **/
    const std::map<int, std::string> KControlsByToken =
    {
        { KTokenPlayer1, "azeqsdwxc" },
        { KTokenPlayer2, "789456123" },
        { KTokenPlayer3, "uiojkl,;:" },
        { KTokenPlayer4, "rtyfghvbn" }
    }; // KControlsByToken initializer list

    /**
    *
    * @brief Main loop, handles just about everything.
    *
    * If you want to start somewhere, this is a good place.
    *
    **/
    int Run ();
} // nsGame
