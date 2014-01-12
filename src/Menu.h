/**
 * @file   Menu.h
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Add item to menu, clear menu, run menu declarations
 *
 **/
#pragma once

#include <functional>
#include <chrono>
#include <vector>

/**
 * 
 * @namespace nsMenu
 * 
 * @brief Namespace containing everything related to the menu system.
 * 
 * 
 **/
namespace nsMenu
{
    /**
     * 
     * @brief Adds an item to menu, which is associated to a callback function, that will be used if said item is the users final choice.
     * 
     **/
    void AddItem (std::string ItemName, std::function<void (void)> Callback = [] () { });

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
     * @param IsWinMenu Replaces the defaut "CatchMe" ASCII art by a nice palm tree by some guy named pjb.
     * 
     **/
    void Run (bool IsWinMenu = false);

    /**
     * 
     * @brief Shows a simple default winning screen announcing the player that won.
     * 
     **/
    void ShowSimpleWinScreen (const std::vector<bool>& PlayerLifeStates, const std::vector<char>& Tokens, const std::vector<unsigned>& TurnCounters);
} // nsMenu