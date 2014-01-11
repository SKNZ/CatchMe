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
        MakeGameMode ("Classic 1v1", 2, 1, false, Classic1v1::GetSize, Classic1v1::MovePlayer, Classic1v1::InitializeRound, Classic1v1::BuildMatrix, Classic1v1::ValidatePlayerPositions, Classic1v1::IsGameOver, Menu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 1v1v1", 3, 1, false, Classic1v1v1::GetSize, Classic1v1v1::MovePlayer, Classic1v1v1::InitializeRound, Classic1v1v1::BuildMatrix, Classic1v1v1::ValidatePlayerPositions, Classic1v1v1::IsGameOver, Menu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 1v1v1v1", 4, 1, false, Classic1v1v1v1::GetSize, Classic1v1v1v1::MovePlayer, Classic1v1v1v1::InitializeRound, Classic1v1v1v1::BuildMatrix, Classic1v1v1v1::ValidatePlayerPositions, Classic1v1v1v1::IsGameOver, Menu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 2v2", 4, 1, false, Classic2v2::GetSize, Classic2v2::MovePlayer, Classic2v2::InitializeRound, Classic2v2::BuildMatrix, Classic2v2::ValidatePlayerPositions, Classic2v2::IsGameOver, Menu::ShowSimpleWinScreen),
        MakeGameMode ("Classic 3v1", 4, 4, false, Classic3v1::GetSize, Classic3v1::MovePlayer, Classic3v1::InitializeRound, Classic3v1::BuildMatrix, Classic3v1::ValidatePlayerPositions, Classic3v1::IsGameOver, Classic3v1::ShowWinScreen),
        
        MakeGameMode ("Survivor 1v1", 2, 1, false, Survivor1v1::GetSize, Survivor1v1::MovePlayer, Survivor1v1::InitializeRound, Survivor1v1::BuildMatrix, Survivor1v1::ValidatePlayerPositions, Survivor1v1::IsGameOver, Menu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 1v1v1", 3, 1, false, Survivor1v1v1::GetSize, Survivor1v1v1::MovePlayer, Survivor1v1v1::InitializeRound, Classic1v1v1::BuildMatrix, Survivor1v1v1::ValidatePlayerPositions, Survivor1v1v1::IsGameOver, Menu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 1v1v1v1", 4, 1, false, Survivor1v1v1v1::GetSize, Survivor1v1v1v1::MovePlayer, Survivor1v1v1v1::InitializeRound, Survivor1v1v1v1::BuildMatrix, Survivor1v1v1v1::ValidatePlayerPositions, Survivor1v1v1v1::IsGameOver, Menu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 2v2", 4, 1, false, Survivor2v2::GetSize, Survivor2v2::MovePlayer, Survivor2v2::InitializeRound, Survivor2v2::BuildMatrix, Survivor2v2::ValidatePlayerPositions, Survivor2v2::IsGameOver, Menu::ShowSimpleWinScreen),
        MakeGameMode ("Survivor 3v1", 4, 4, false, Survivor3v1::GetSize, Survivor3v1::MovePlayer, Survivor3v1::InitializeRound, Survivor3v1::BuildMatrix, Survivor3v1::ValidatePlayerPositions, Survivor3v1::IsGameOver, Survivor3v1::ShowWinScreen),
    };

    /**
     * 
     * An id for each token
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
}
