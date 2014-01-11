#pragma once

#include <vector>

#include "../Game.h"

namespace Helpers
{
    void MovePlayer (const Game::CMatrix& Matrix, Game::CPosition& PlayerPosition, const Game::CPosition& MatrixSize, const Game::PlayerMovesY MoveY, const Game::PlayerMovesX MoveX);
	void ValidatePlayerPositionsNoTeam (const Game::CPositions& PlayerPositions, unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates);

    /**
     * 
     * @brief Loads the obstacles positions from the file.
     * 
     * @todo Opens the file every time. Stupid.
     * 
     **/
	void LoadObstaclesFromFile (Game::CPositions& ObstaclesPositions, const Game::CPosition& MaxSize);

    /**
     * 
     * @brief Adds the obstacle and player tokens to the matrix.
     * 
     **/
    void AddObstaclesAndPlayersToMatrix (Game::CMatrix& Matrix, const Game::CPositions& PlayerPositions,
                                         const std::vector<bool>& PlayerLifeStates, const Game::CPositions& ObstaclesPositions, char EmptyToken);
}