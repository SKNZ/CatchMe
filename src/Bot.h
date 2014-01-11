/**
 * @file   Bot.h
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Bot logic
 *
 **/
#pragma once

#include "GameMode.h"

namespace nsGame
{
    namespace nsBot
    {
        using namespace nsGame;

        /**
         * 
         * @brief Finds if a player is in attack range, attack if yes else find neareast player
         *          and calculate first element of path towards him.
         * 
         */
        void MakeMove (const CMatrix& Matrix, const std::vector<bool>& PlayerLifeStates, CPositions& PlayerPositions, const unsigned CurrentPlayer);
    } // nsBot
} // nsGame