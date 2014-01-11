/**
 * @file   Survivor1v1.h
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Survivor 1v1 game mode
 *
 **/
#pragma once

#include <vector>

#include "../GameMode.h"

namespace NSSurvivor1v1
{
    using namespace NSGame;

    void GetSize (CPosition& Size);

    void MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX);

    void InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize);

    void BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const std::vector<bool>& PlayerLifeStates, const char EmptyToken);

    void ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates);

    bool IsGameOver (const std::vector<bool>& PlayerLifeStates);
}
