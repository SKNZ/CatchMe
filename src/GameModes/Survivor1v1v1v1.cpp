/**
 * @file   Survivor1v1v1v1.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Survivor1v1v1v1 game mode
 *
 **/
#include <algorithm>

#include "Survivor1v1v1v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
	nsGame::CPositions ObstaclesPositions;
}

void nsSurvivor1v1v1v1::GetSize (CPosition& Size)
{
    nsMenu::Clear ();

    nsMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    nsMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    nsMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    nsMenu::Run ();
}

void nsSurvivor1v1v1v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    nsHelpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
}

void nsSurvivor1v1v1v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    nsHelpers::ValidatePlayerPositionsNoTeam (PlayerPositions, CurrentPlayer, PlayerLifeStates);

    for (CPosition Position : ObstaclesPositions)
            if (PlayerPositions [CurrentPlayer] == Position)
                PlayerLifeStates [CurrentPlayer] = false;

    if(PlayerLifeStates [CurrentPlayer] && find (ObstaclesPositions.cbegin(), ObstaclesPositions.cend(), PlayerPositions [CurrentPlayer]) == ObstaclesPositions.cend())
        ObstaclesPositions.push_back (PlayerPositions [CurrentPlayer]);
} // ValidatePlayerPositions

void nsSurvivor1v1v1v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top rightc
    PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
    PlayerPositions [2] = { 0, 0}; // Top left
    PlayerPositions [3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right

    ObstaclesPositions.clear ();
    nsHelpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);
} // InitializeRound

void nsSurvivor1v1v1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    nsHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
}

bool nsSurvivor1v1v1v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    unsigned DeadPlayerCount = 0;

    for (bool PlayerState : PlayerLifeStates)
        if (!PlayerState)
            ++DeadPlayerCount;

    return DeadPlayerCount == 3;
}
