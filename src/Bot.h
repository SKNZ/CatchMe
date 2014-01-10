#pragma once

#include "GameMode.h"

namespace Game
{
    namespace Bot
    {
        using namespace Game;
        
        void MakeMove (const CMatrix& Matrix, const std::vector<bool>& PlayerLifeStates, CPositions& PlayerPositions, unsigned CurrentPlayer);
    }
}