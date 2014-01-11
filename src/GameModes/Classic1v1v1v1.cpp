#include "Classic1v1v1v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
    Game::CPositions ObstaclesPositions;
}

void Classic1v1v1v1::GetSize (CPosition& Size)
{
    Menu::Clear ();

    Menu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    Menu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    Menu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    Menu::Run ();
}

void Classic1v1v1v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    Helpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
}

void Classic1v1v1v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
	Helpers::ValidatePlayerPositionsNoTeam (PlayerPositions, CurrentPlayer, PlayerLifeStates);
}

void Classic1v1v1v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top rightc
    PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
    PlayerPositions [2] = { 0, 0}; // Top left
    PlayerPositions [3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right
    
    ObstaclesPositions.clear ();
    Helpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);
}

void Classic1v1v1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    Helpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
}

bool Classic1v1v1v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    unsigned DeadPlayerCount = 0;

    for (bool PlayerState : PlayerLifeStates)
        if (!PlayerState)
            ++DeadPlayerCount;

    return DeadPlayerCount == 3;
}