#include <algorithm>

#include "Survivor1v1v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
	NSGame::CPositions ObstaclesPositions;
}

void NSSurvivor1v1v1::GetSize (CPosition& Size)
{
    NSMenu::Clear ();

    NSMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    NSMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    NSMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    NSMenu::Run ();
}

void NSSurvivor1v1v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    NSHelpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
}

void NSSurvivor1v1v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
	NSHelpers::ValidatePlayerPositionsNoTeam (PlayerPositions, CurrentPlayer, PlayerLifeStates);

    for (CPosition Position : ObstaclesPositions)
        if (PlayerPositions [CurrentPlayer] == Position)
            PlayerLifeStates [CurrentPlayer] = false;

    // If he just died, there will be someone else on his spot, so no obstacle yet.
    if(PlayerLifeStates [CurrentPlayer] && find (ObstaclesPositions.cbegin(), ObstaclesPositions.cend(), PlayerPositions [CurrentPlayer]) == ObstaclesPositions.cend())
        ObstaclesPositions.push_back (PlayerPositions [CurrentPlayer]);
} // ValidatePlayerPositions

void NSSurvivor1v1v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
    PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
    PlayerPositions [2] = { 0, 0 }; // Top left

    ObstaclesPositions.clear ();
    NSHelpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);
} // InitializeRound

void NSSurvivor1v1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    NSHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
}

bool NSSurvivor1v1v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    unsigned DeadPlayerCount = 0;

    for (bool PlayerState : PlayerLifeStates)
        if (!PlayerState)
            ++DeadPlayerCount;

    return DeadPlayerCount == 2;
}
