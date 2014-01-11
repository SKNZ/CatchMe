#include "Classic1v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
    NSGame::CPositions ObstaclesPositions;
}

void NSClassic1v1::GetSize (CPosition& Size)
{
    NSMenu::Clear ();

    NSMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    NSMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });

    NSMenu::Run ();
}

void NSClassic1v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    NSHelpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
}

void NSClassic1v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    NSHelpers::ValidatePlayerPositionsNoTeam (PlayerPositions, CurrentPlayer, PlayerLifeStates);
}

void NSClassic1v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
    PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
    
    ObstaclesPositions.clear ();
    NSHelpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);
}

void NSClassic1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    NSHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
}

bool NSClassic1v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{    
    return !PlayerLifeStates [0] || !PlayerLifeStates [1];
}
