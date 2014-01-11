/**
 * @file   Game.h
 *
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Main game header, contains game modes, tokens (+ enum), controls, and main function.
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

#include "Menu.h"

namespace NSGame
{
    /**
    *
    * @brief All the game modes.
    *
    **/
    const std::vector<SGameMode> KGameModes =
    {
        MakeGameMode ("Classic 1v1", 2, 1, false, NSClassic1v1::GetSize, NSClassic1v1::MovePlayer, NSClassic1v1::InitializeRound, NSClassic1v1::BuildMatrix, NSClassic1v1::ValidatePlayerPositions, NSClassic1v1::IsGameOver, NSMenu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 1v1v1", 3, 1, false, NSClassic1v1v1::GetSize, NSClassic1v1v1::MovePlayer, NSClassic1v1v1::InitializeRound, NSClassic1v1v1::BuildMatrix, NSClassic1v1v1::ValidatePlayerPositions, NSClassic1v1v1::IsGameOver, NSMenu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 1v1v1v1", 4, 1, false, NSClassic1v1v1v1::GetSize, NSClassic1v1v1v1::MovePlayer, NSClassic1v1v1v1::InitializeRound, NSClassic1v1v1v1::BuildMatrix, NSClassic1v1v1v1::ValidatePlayerPositions, NSClassic1v1v1v1::IsGameOver, NSMenu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 2v2", 4, 1, false, NSClassic2v2::GetSize, NSClassic2v2::MovePlayer, NSClassic2v2::InitializeRound, NSClassic2v2::BuildMatrix, NSClassic2v2::ValidatePlayerPositions, NSClassic2v2::IsGameOver, NSMenu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 3v1", 4, 4, false, NSClassic3v1::GetSize, NSClassic3v1::MovePlayer, NSClassic3v1::InitializeRound, NSClassic3v1::BuildMatrix, NSClassic3v1::ValidatePlayerPositions, NSClassic3v1::IsGameOver, NSClassic3v1::ShowWinScreen),

        MakeGameMode ("Survivor 1v1", 2, 1, false, NSSurvivor1v1::GetSize, NSSurvivor1v1::MovePlayer, NSSurvivor1v1::InitializeRound, NSSurvivor1v1::BuildMatrix, NSSurvivor1v1::ValidatePlayerPositions, NSSurvivor1v1::IsGameOver, NSMenu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 1v1v1", 3, 1, false, NSSurvivor1v1v1::GetSize, NSSurvivor1v1v1::MovePlayer, NSSurvivor1v1v1::InitializeRound, NSSurvivor1v1v1::BuildMatrix, NSSurvivor1v1v1::ValidatePlayerPositions, NSSurvivor1v1v1::IsGameOver, NSMenu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 1v1v1v1", 4, 1, false, NSSurvivor1v1v1v1::GetSize, NSSurvivor1v1v1v1::MovePlayer, NSSurvivor1v1v1v1::InitializeRound, NSSurvivor1v1v1v1::BuildMatrix, NSSurvivor1v1v1v1::ValidatePlayerPositions, NSSurvivor1v1v1v1::IsGameOver, NSMenu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 2v2", 4, 1, false, NSSurvivor2v2::GetSize, NSSurvivor2v2::MovePlayer, NSSurvivor2v2::InitializeRound, NSSurvivor2v2::BuildMatrix, NSSurvivor2v2::ValidatePlayerPositions, NSSurvivor2v2::IsGameOver, NSMenu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 3v1", 4, 4, false, NSSurvivor3v1::GetSize, NSSurvivor3v1::MovePlayer, NSSurvivor3v1::InitializeRound, NSSurvivor3v1::BuildMatrix, NSSurvivor3v1::ValidatePlayerPositions, NSSurvivor3v1::IsGameOver, NSSurvivor3v1::ShowWinScreen),
    };

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
    };

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
    };

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
    };

    /**
    *
    * @brief Main loop, handles just about everything.
    *
    * If you want to start somewhere, this is a good place.
    *
    **/
    int Run ();
} // NSGame
