#include <sstream>
#include <algorithm>

#include "Survivor3v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
	Game::CPositions ForbiddenPositions;
	Game::CPositions AuthorizedAlonePositions;
    array<unsigned, 4> AlonePlayerTurnCounters;

    int AlonePlayer = -1;
}

void Survivor3v1::GetSize (CPosition& Size)
{
    Menu::Clear ();
    
//     Menu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    Menu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    Menu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    Menu::Run ();
}

void Survivor3v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    Helpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
}

void Survivor3v1::ValidatePlayerPositions (const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
    {
        if (i == CurrentPlayer || !PlayerLifeStates [i] || CurrentPlayer != AlonePlayer) 
            continue;

        if (PlayerPositions [CurrentPlayer] == PlayerPositions [i] && i == AlonePlayer)
            PlayerLifeStates[i] = false;
    }

    if (CurrentPlayer != AlonePlayer)
    {
        if (find(ForbiddenPositions.cbegin(), ForbiddenPositions.cend(), PlayerPositions [CurrentPlayer]) == ForbiddenPositions.cend()) 
            ForbiddenPositions.push_back (PlayerPositions [CurrentPlayer]);
        else
            PlayerLifeStates [CurrentPlayer] = false;
    }
    else
    {
		AlonePlayerTurnCounters [AlonePlayer]++;
    }
}

void Survivor3v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
    PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
    PlayerPositions [2] = { 0, 0 }; // Top left
    PlayerPositions [3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right
    
    ++AlonePlayer;
    ForbiddenPositions.clear ();
}

void Survivor3v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    for (CLine& Line : Matrix)
        fill (Line.begin (), Line.end (), EmptyToken);

    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
        if (PlayerLifeStates[i])
            Matrix [PlayerPositions [i].first] [PlayerPositions [i].second] = Game::KTokens [i];

    std::stringstream FileName;
    FileName << "./" << Matrix.size() << "_" << Matrix.begin()->size() << ".map";

    Helpers::LoadObstaclesFromFile (Matrix, FileName.str());
}

bool Survivor3v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    return !PlayerLifeStates [AlonePlayer];
}

void Survivor3v1::ShowWinScreen (const std::vector< bool >& PlayerLifeStates, std::vector<char> Tokens, vector<unsigned> TurnCounters)
{
    Menu::Clear ();

    for (unsigned i = 0; i < 4; ++i)
    {
        stringstream Winner;
        Winner << "Player " << i << " lasted " << AlonePlayerTurnCounters [i] << " rounds.";
        Menu::AddItem(Winner.str(), [] () {} );
    }

    Menu::Run (true);
}

