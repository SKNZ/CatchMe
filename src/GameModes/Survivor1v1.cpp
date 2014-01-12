/**
 * @file   Survivor1v1.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Survivor 1v1 game mode
 *
 **/
#include <algorithm>

#include "Survivor1v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
	nsGame::CPositions ObstaclesPositions;
} // namespace

void nsSurvivor1v1::GetSize (CPosition& Size)
{
    nsMenu::Clear ();

    nsMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    nsMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });

    nsMenu::Run ();
} // GetSize

void nsSurvivor1v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    int DiffX = static_cast<int> (MoveX);
    int DiffY = static_cast<int> (MoveY);

    // Comparing first and second separately allows player to 
    if (PlayerPosition.first + DiffY >= 0 && PlayerPosition.first + DiffY < MatrixSize.first)
        PlayerPosition.first += DiffY;

    if (PlayerPosition.second + DiffX >= 0 && PlayerPosition.second + DiffX < MatrixSize.second)
        PlayerPosition.second += DiffX;
} // MovePlayer

void nsSurvivor1v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    nsHelpers::ValidatePlayerPositionsNoTeam (PlayerPositions, CurrentPlayer, PlayerLifeStates);

	for (CPosition Position : ObstaclesPositions)
			if (PlayerPositions [CurrentPlayer] == Position)
				PlayerLifeStates [CurrentPlayer] = false;

    if(find (ObstaclesPositions.cbegin(), ObstaclesPositions.cend(), PlayerPositions [CurrentPlayer]) == ObstaclesPositions.cend())
        ObstaclesPositions.push_back (PlayerPositions [CurrentPlayer]);
} // ValidatePlayerPositions

void nsSurvivor1v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
    PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left

    ObstaclesPositions.clear ();
    nsHelpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);
} // InitializeRound

void nsSurvivor1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    nsHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
} // BuildMatrix

bool nsSurvivor1v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{    
    return !PlayerLifeStates [0] || !PlayerLifeStates [1];
} // IsGameOver
