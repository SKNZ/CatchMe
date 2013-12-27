#include "Classic1v1v1v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

void Classic1v1v1v1::GetSize (CPosition& Size)
{
    Menu::Clear ();
    
    Menu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    Menu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    Menu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });
    Menu::AddItem ("Greater map", [&Size] () { Size = { 40, 80 }; });
    

    Menu::Run ();
}

void Classic1v1v1v1::MovePlayer (CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    Helpers::MovePlayer(PlayerPosition, MatrixSize, MoveY, MoveX);
}

void Classic1v1v1v1::ValidatePlayerPositions (CPositions PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
    {
        if (i == CurrentPlayer || !PlayerLifeStates[i])
            continue;

        if (PlayerPositions[CurrentPlayer].first == PlayerPositions[i].first
            && PlayerPositions[CurrentPlayer].second == PlayerPositions[i].second)
        {
            PlayerLifeStates[i] = false;
            break;
        }
    }
}

void Classic1v1v1v1::InitializePlayerPositions (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    for (unsigned i = 0; i < PlayerCount; ++i)
    {
        switch (i)
        {
            case 0:
                PlayerPositions[0] = { 0, MaxSize.second - 1 }; // Top rightc
                break;
            case 1:
                PlayerPositions[1] = { MaxSize.first - 1, 0 }; // Bottom left
                break;
            case 2:
                PlayerPositions[2] = { 0, 0}; // Top left
                break;
            case 3:
                PlayerPositions[3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right
                break;
        }
    }
}

void Classic1v1v1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    for (CLine& Line : Matrix)
        fill (Line.begin (), Line.end (), EmptyToken);

    for (unsigned i = 0; i < PlayerPositions.size(); ++i)
        if (PlayerLifeStates[i])
            Matrix [PlayerPositions [i].first] [PlayerPositions [i].second] = Game::KTokens [i];
}


bool Classic1v1v1v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    unsigned DeadPlayerCount = 0;

    for (bool PlayerState : PlayerLifeStates)
        if (!PlayerState)
            ++DeadPlayerCount;

    return DeadPlayerCount == 3;
}