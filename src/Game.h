#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <chrono>

namespace Game
{
    enum struct PlayerMovesX : int
    {
        KUp   = -1,
        KStay = 0,
        KDown = 1,
    };

    enum struct PlayerMovesY : int
    {
        KLeft  = -1,
        KStay  = 0,
        KRight = 1,
    };
    
    typedef std::vector<char>       CLine;
    typedef std::vector<CLine>      CMatrix;
    typedef std::pair<int, int>     CPosition;
    typedef std::vector<CPosition>  CPositions;

    // Constants
    const std::pair<unsigned, unsigned> KMatrixSize              = { 10, 20 }; // Y, X
    const unsigned                      KMaxPlayerCount          = 4;
    const unsigned                      KMinPlayerCount          = 2; // @todo This should be lowered to one if/once the "Player vs Computer" mode is ready.

    /**
     * 
     * The duration during which the game will be suspended to let the player read the error message.
     * 
     * @warning This should only be used for gameplay related error messages, such as wrong key
     *          and not for technical problems (such as exceptions reports).
     * 
     */
    const std::chrono::milliseconds     KErrorMessageDisplayTime(2000);

    /**
     * 
     * The interval between each render loop.
     * 
     */
    const std::chrono::milliseconds     KRenderLoopInterval(100);

    /**
     *
     * @brief List of all the possible tokens.
     * 
     * A token is an item that occupies a case on the grid, such as nothing, a player, or an obstacle.
     * These, however, do not include the borders.
     * 
     **/
    const std::vector<char> KTokens =
    {
        'X',
        'O',
        '#',
        '@',
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
    const std::map<char, std::string> KControlsByToken =
    {
        { 'X', "azeqsdwxc" },
        { 'O', "789456123" },
        { '#', "uiojkl,;:" },
        { '@', "rtyfghvbn" }
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