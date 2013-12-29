#pragma once

#include <vector>
#include "../GameMode.h"

namespace Classic1v1
{
    using namespace Game;

    void GetSize (CPosition& Size);

    void MovePlayer (CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX);

    void InitializePlayerPositions (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize);

    void BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const std::vector<bool>& PlayerLifeStates, const char EmptyToken);
    
	void ValidatePlayerPositions(const CPositions& PlayerPositions, unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates);
    
    bool IsGameOver (const std::vector<bool>& PlayerLifeStates);
}
