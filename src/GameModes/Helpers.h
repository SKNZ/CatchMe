/**
 * @file   Helpers.h
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Redundant code about player movement, player positions validation, obstacles loading, matrix building
 *
 **/
#pragma once

#include <vector>

#include "../Game.h"

namespace nsHelpers
{
    /**
     * 
     * @brief Checks for boundaries, obstacles and moves the player.
     * 
     **/
    void MovePlayer (const nsGame::CMatrix& Matrix, nsGame::CPosition& PlayerPosition, const nsGame::CPosition& MatrixSize,
                     const nsGame::PlayerMovesY MoveY, const nsGame::PlayerMovesX MoveX);
    
    /**
     * 
     * @brief Checks if a player is in a position that is lethal, and if yes, KILL IT !
     * 
     **/
	void ValidatePlayerPositionsNoTeam (const nsGame::CPositions& PlayerPositions, const unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates);

    /**
     * 
     * @brief Loads the obstacles positions from file.
     * 
     * The format of file should be one pair per line in the following format: Y X
     * There is a single space between each value.
     * 
     **/
	void LoadObstaclesFromFile (nsGame::CPositions& ObstaclesPositions, const nsGame::CPosition& MaxSize);

    /**
     * 
     * @brief Adds the obstacle and player tokens to the matrix.
     * 
     **/
    void AddObstaclesAndPlayersToMatrix (nsGame::CMatrix& Matrix, const nsGame::CPositions& PlayerPositions,
                                         const std::vector<bool>& PlayerLifeStates, const nsGame::CPositions& ObstaclesPositions, char EmptyToken);
} // nsHelpers