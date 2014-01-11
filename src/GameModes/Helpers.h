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

namespace NSHelpers
{
    /**
     * 
     * @brief Checks for boundaries, obstacles and moves the player.
     * 
     **/
    void MovePlayer (const NSGame::CMatrix& Matrix, NSGame::CPosition& PlayerPosition, const NSGame::CPosition& MatrixSize,
                     const NSGame::PlayerMovesY MoveY, const NSGame::PlayerMovesX MoveX);
    
    /**
     * 
     * @brief Checks if a player is in a position that is lethal, and if yes, KILL IT !
     * 
     **/
	void ValidatePlayerPositionsNoTeam (const NSGame::CPositions& PlayerPositions, unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates);

    /**
     * 
     * @brief Loads the obstacles positions from file.
     * 
     * The format of file should be one pair per line in the following format: Y X
     * There is a single space between each value.
     * 
     **/
	void LoadObstaclesFromFile (NSGame::CPositions& ObstaclesPositions, const NSGame::CPosition& MaxSize);

    /**
     * 
     * @brief Adds the obstacle and player tokens to the matrix.
     * 
     **/
    void AddObstaclesAndPlayersToMatrix (NSGame::CMatrix& Matrix, const NSGame::CPositions& PlayerPositions,
                                         const std::vector<bool>& PlayerLifeStates, const NSGame::CPositions& ObstaclesPositions, char EmptyToken);
} // NSHelpers