#include "Survivor2v2.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

#include <sstream>
#include <algorithm>

using namespace std;

namespace
{
	Game::CPositions ForbiddenPositions;
}

void Survivor2v2::GetSize (CPosition& Size)
{
    Menu::Clear ();
    
    Menu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    Menu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    Menu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });
    Menu::AddItem ("Greater map", [&Size] () { Size = { 40, 80 }; });
    

    Menu::Run ();
}

void Survivor2v2::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    Helpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
}

void Survivor2v2::ValidatePlayerPositions (const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
    {
        if (i == CurrentPlayer || !PlayerLifeStates[i] || (i + CurrentPlayer) % 2 == 0) // Player 1 & 3 and 2 & 4 are teamed up.
            continue;
			
        if (PlayerPositions [CurrentPlayer].first == PlayerPositions [i].first
                && PlayerPositions [CurrentPlayer].second == PlayerPositions [i].second)
        {
            PlayerLifeStates[i] = false;
        }
    }
    	
	for (CPosition Position : ForbiddenPositions)
		for (unsigned i = 0; i < 4; ++i)
			if (PlayerPositions [i] == Position)
				PlayerLifeStates [i] = false;

	for (CPosition Position : PlayerPositions)
		if(find (ForbiddenPositions.cbegin(), ForbiddenPositions.cend(), Position) == ForbiddenPositions.cend())
			ForbiddenPositions.push_back (Position);
}

void Survivor2v2::InitializePlayerPositions (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    for (unsigned i = 0; i < PlayerCount; ++i)
    {
        switch (i)
        {
            case 0:
                PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
                break;
            case 1:
                PlayerPositions [1] = { 0, 0 }; // Top left
                break;
            case 2:
                PlayerPositions [2] = { MaxSize.first - 1, 0 }; // Bottom left
                break;
            case 3:
                PlayerPositions [3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right
                break;
        }
    }
}

void Survivor2v2::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    for (CLine& Line : Matrix)
        fill (Line.begin (), Line.end (), EmptyToken);

    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
        if (PlayerLifeStates[i])
            Matrix [PlayerPositions [i].first] [PlayerPositions [i].second] = Game::KTokens [i];

    std::stringstream FileName;
    FileName << "./survivor2v2_" << Matrix.size() << "_" << Matrix.begin()->size() << ".map";

    Helpers::LoadObstaclesFromFile (Matrix, FileName.str());
}

bool Survivor2v2::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    return (!PlayerLifeStates[0] && !PlayerLifeStates[2]) || (!PlayerLifeStates[1] && !PlayerLifeStates[3]);
}

