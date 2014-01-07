#include "Survivor1v1.h"
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

void Survivor1v1::GetSize (CPosition& Size)
{
    Menu::Clear ();
    
    Menu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    Menu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });

    Menu::Run ();
}

void Survivor1v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{	
    int DiffX = static_cast<int> (MoveX);
    int DiffY = static_cast<int> (MoveY);
    
    if (PlayerPosition.first + DiffY >= 0 && PlayerPosition.first + DiffY < MatrixSize.first)
        PlayerPosition.first += DiffY;

    if (PlayerPosition.second + DiffX >= 0 && PlayerPosition.second + DiffX < MatrixSize.second)
        PlayerPosition.second += DiffX;
}

void Survivor1v1::ValidatePlayerPositions (const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    Helpers::ValidatePlayerPositionsNoTeam (PlayerPositions, CurrentPlayer, PlayerLifeStates);
    	
	for (CPosition Position : ForbiddenPositions)
		for (unsigned i = 0; i < 4; ++i)
			if (PlayerPositions [i] == Position)
				PlayerLifeStates [i] = false;

	for (CPosition Position : PlayerPositions)
		if(find (ForbiddenPositions.cbegin(), ForbiddenPositions.cend(), Position) == ForbiddenPositions.cend())
			ForbiddenPositions.push_back (Position);
}

void Survivor1v1::InitializePlayerPositions (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
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
                PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
                break;
        }
    }
}

void Survivor1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    for (CLine& Line : Matrix)
        fill (Line.begin (), Line.end (), EmptyToken);

    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
        if (PlayerLifeStates[i])
            Matrix [PlayerPositions [i].first] [PlayerPositions [i].second] = Game::KTokens [i];

    std::stringstream FileName;
    FileName << "survivor1v1_" << Matrix.size() << "_" << Matrix.begin()->size() << ".map";

    Helpers::LoadObstaclesFromFile (Matrix, FileName.str());
}

bool Survivor1v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{    
    return !PlayerLifeStates [0] || !PlayerLifeStates [1];
}
