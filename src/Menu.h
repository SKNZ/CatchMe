#pragma once

#include <functional>
#include <chrono>
#include <vector>

namespace Menu
{
    /**
     * 
     * @brief The timer before the error message disappears
     * 
     * 
     */
    const unsigned KErrorMessageDisplayTime = 1000;
    
    /**
     * 
     * @brief Adds an item to menu, which is associated to a callback function, that will be used if said item is the users final choice.
     * 
     **/
    void AddItem (std::string ItemName, std::function<void (void)> Callback);
    
    /**
     * 
     * @brief Clears up the previous entries of the menu.
     * 
     **/
    void Clear ();
    
    /**
     * 
     * @brief Displays the menu, and gets the user selection.
     * 
     * @todo Look at adding arrow keys support for menu browsing... Maybe factorize colors ?
     * 
     **/
    void Run (bool IsWinMenu = false);
        
    /**
        * 
        * Shows a simple default winning screen announcing the player that won.
        * 
        **/
    void ShowSimpleWinScreen (const std::vector<bool>& PlayerLifeStates, std::vector<char> Tokens, std::vector<unsigned> TurnCounters);
}