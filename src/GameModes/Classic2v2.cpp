/**
 * @file   Classic2v2.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Classic 2v2 game mode
 *
 **/
#include "Classic2v2.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
    nsGame::CPositions ObstaclesPositions;
} // namespace

void nsClassic2v2::GetSize (CPosition& Size)
{
    nsMenu::Clear ();

    nsMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    nsMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    nsMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    nsMenu::Run ();
} // GetSize

void nsClassic2v2::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    nsHelpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
} // MovePlayer

void nsClassic2v2::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
    {
        if (i == CurrentPlayer || !PlayerLifeStates[i] || (i + CurrentPlayer) % 2 == 0) // Player 1 & 3 and 2 & 4 are teamed up.
            continue;

        if (PlayerPositions [CurrentPlayer] == PlayerPositions [i])
            PlayerLifeStates[i] = false;
    }
} // ValidatePlayerPositions

void nsClassic2v2::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
    PlayerPositions [1] = { 0, 0 }; // Top left
    PlayerPositions [2] = { MaxSize.first - 1, 0 }; // Bottom left
    PlayerPositions [3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right

    ObstaclesPositions.clear ();
    nsHelpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);

    nsMenu::Clear ();

    nsMenu::AddItem ("The players 'X' and '#' form a team against the players 'O' and '@'.");

    nsMenu::Run ();
} // InitializeRound

void nsClassic2v2::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    nsHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
} // BuildMatrix

bool nsClassic2v2::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    return (!PlayerLifeStates[0] && !PlayerLifeStates[2]) || (!PlayerLifeStates[1] && !PlayerLifeStates[3]);
} // IsGameOver
