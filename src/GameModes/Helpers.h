#pragma once

#include <vector>

#include "../Game.h"

namespace Helpers
{
    void MovePlayer (const Game::CMatrix& Matrix, Game::CPosition& PlayerPosition, const Game::CPosition& MatrixSize, const Game::PlayerMovesY MoveY, const Game::PlayerMovesX MoveX);
	void ValidatePlayerPositionsNoTeam (const Game::CPositions& PlayerPositions, unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates);

    /**
     * 
     * @todo Opens the file every time. Stupid.
     * 
     **/
	void LoadObstaclesFromFile (Game::CMatrix& Matrix, std::string FileName);
}