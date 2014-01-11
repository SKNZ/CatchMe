/**
 * @file   GameMode.h
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  SGameMode definition, enum for axis moves, typedefs, constructor function declaration
 *
 **/
#pragma once

#include <vector>
#include <functional>

namespace NSGame
{
    /**
     * 
     * @brief Moves on the Y axis.
     * 
     **/
    enum struct PlayerMovesY : int
    {
        KUp   = -1,
        KStay = 0,
        KDown = 1,
    };

    /**
     * 
     * @brief Moves on the X axis.
     * 
     **/
    enum struct PlayerMovesX : int
    {
        KLeft  = -1,
        KStay  = 0,
        KRight = 1,
    };

    typedef std::vector<char>       CLine;
    typedef std::vector<CLine>      CMatrix;
    typedef std::pair<int, int>     CPosition;
    typedef std::vector<CPosition>  CPositions;

    typedef std::function<void (CPosition& Size)> FGetSize;

    typedef std::function<void (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize,
                                const PlayerMovesY MoveY, const PlayerMovesX MoveX)> FMovePlayer;

    typedef std::function<void (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& Size)> FInitializeRound;

    typedef std::function<void (CMatrix& Matrix, const CPositions& PlayerPositions,
                                const std::vector<bool>& PlayerLifeStates, const char EmptyToken)> FBuildMatrix;

    typedef std::function<void (const CMatrix& Matrix, CPositions PlayerPositions, unsigned CurrentPlayer,
                                std::vector<bool>& PlayerLifeStates)> FValidatePlayerPositions;

    typedef std::function<bool (const std::vector<bool>& PlayerLifeStates)> FIsGameOver;

    typedef std::function<void (const std::vector<bool>& PlayerLifeStates, std::vector<char> Tokens,
                                std::vector<unsigned> TurnCounters)> FShowWinScreen;

    /**
     * 
     * @brief A game mode !
     * 
     **/
    struct SGameMode
    {
        /**
         * 
         * @brief The name of the game mode.
         * 
         */
        std::string Name;
        
        /**
         * 
         * @brief The number of players that will play the game. Limited to 4 because max 4 sets of controls...
         * 
         */
        unsigned PlayerCount;
        
        /**
         * 
         * @brief The number of rounds that must be played before a winner can be declared.
         * 
         **/
        unsigned RoundCount;
        
        /**
         * 
         * @brief If a player is allowed not to move on purpose at any time (skip his turn).
         * 
         **/
        bool AllowStay;
        
        /**
         * 
         * @brief Size of the grid.
         * 
         **/
        FGetSize GetSize;
        
        /**
         * 
         * @brief Moves a player in a certain direction, checks for walls and plays beeping sound if wall is hit (last part is not tested).
         * 
         **/
        FMovePlayer MovePlayer;
        
        /**
         * 
         * @brief Each player gets a corner of the grid.
         * 
         * Ex:
         *  Player 1 is top right.
         *  Player 2 is bottom left.
         *  Player 3 is top left.
         *  Player 4 is bottom right.
         * 
         **/
        FInitializeRound InitializeRound;
        
        /**
         * 
         * @brief Update the Matrix to reflect the new positions of the players, barriers etc etc.
         * 
         **/
        FBuildMatrix BuildMatrix;
    
        /**
         * 
         * @brief Checks if a players position overlaps with another one.
         * 
         **/
        FValidatePlayerPositions ValidatePlayerPositions;
        
        /**
         * 
         * @brief Whether or not the game is over.
         * 
         **/
        FIsGameOver IsGameOver;
        
        /**
         * 
         * @brief Show the win screen.
         * 
         **/
        FShowWinScreen ShowWinScreen;
    }; // SGameMode

    /**
     * 
     * @brief Constructor of the SGameMode structure.
     * 
     **/
    SGameMode MakeGameMode (std::string Name, unsigned PlayerCount, unsigned RoundCount, bool AllowStay,
        FGetSize GetSize,
        FMovePlayer MovePlayer,
        FInitializeRound InitializeRound,
        FBuildMatrix BuildMatrix,
        FValidatePlayerPositions ValidatePlayerPositions,
        FIsGameOver IsGameOver,
        FShowWinScreen ShowWinScreen);
} // NSGame
