#pragma once

#include "GameMode.h"

namespace NSGame
{
    namespace NSBot
    {
        using namespace NSGame;

        /**
         * 
         * @brief Finds if a player is in attack range, attack if yes else find neareast player
         *          and calculate first element of path towards him.
         * 
         */
        void MakeMove (const CMatrix& Matrix, const std::vector<bool>& PlayerLifeStates, CPositions& PlayerPositions, unsigned CurrentPlayer);
    } // NSBot
} // NSGame