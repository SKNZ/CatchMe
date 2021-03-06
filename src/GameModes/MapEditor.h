/**
 * @file   MapEditor.h
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Map editor for obstacles
 *
 **/
#pragma once

#include <vector>

#include "../GameMode.h"

/**
 *
 * @namespace nsMapEditor
 * 
 * @brief Namespace containing everything related to MapEditor functionality.
 * 
 **/
namespace nsMapEditor
{
    using namespace nsGame;

    void GetSize (CPosition& Size);

    void MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX);

    void InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize);

    void BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const std::vector<bool>& PlayerLifeStates, const char EmptyToken);

    void ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, const unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates);

    bool IsGameOver (const std::vector<bool>& PlayerLifeStates);

    void ShowWinScreen (const std::vector<bool>& PlayerLifeStates, const std::vector<char>& Tokens, const std::vector<unsigned>& TurnCounters);
} // nsMapEditor
