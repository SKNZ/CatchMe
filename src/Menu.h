#pragma once

#include <functional>
#include <chrono>

namespace Menu
{
    /**
     * 
     * @brief The timer before the error message disappears
     * 
     * 
     */
    const std::chrono::milliseconds KErrorMessageDisplayTime (1000);
    
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
     **/
    void Run ();
}