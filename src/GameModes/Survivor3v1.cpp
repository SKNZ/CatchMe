#include <algorithm>
#include <sstream>

#include "Survivor3v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
	NSGame::CPositions ObstaclesPositions;
    array<unsigned, 4> AlonePlayerTurnCounters;

    int AlonePlayer = -1;
}

void Survivor3v1::GetSize (CPosition& Size)
{
    NSMenu::Clear ();

    NSMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    NSMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    NSMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    NSMenu::Run ();
}

void Survivor3v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    Helpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
}

void Survivor3v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    if (CurrentPlayer == AlonePlayer)
    {
		AlonePlayerTurnCounters [AlonePlayer]++;
    }
    else
    {
        if (PlayerPositions [CurrentPlayer] == PlayerPositions [AlonePlayer])
            PlayerLifeStates [AlonePlayer] = false;

        if (find(ObstaclesPositions.cbegin(), ObstaclesPositions.cend(), PlayerPositions [CurrentPlayer]) == ObstaclesPositions.cend()) // If Position is not obstacle
            ObstaclesPositions.push_back (PlayerPositions [CurrentPlayer]);
        else
            PlayerLifeStates [CurrentPlayer] = false;
    }

    int Y = PlayerPositions [CurrentPlayer].first, X = PlayerPositions [CurrentPlayer].second;

    bool SurroundedByObstacles = true;
    for (int i = -1; i < 1; ++i)
        for (int j = -1; i < 1; ++i)
            if (Matrix [Y + i] [X + j] != KTokens [KTokenObstacle])
                SurroundedByObstacles = false;

    if (SurroundedByObstacles)
        PlayerLifeStates [CurrentPlayer] = false;
}

void Survivor3v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
    PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
    PlayerPositions [2] = { 0, 0 }; // Top left
    PlayerPositions [3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right

    ++AlonePlayer;

    NSMenu::Clear ();

    std::stringstream Text;
    Text << "The lone player is '" << KTokens [AlonePlayer] << '.';
    NSMenu::AddItem (Text.str ());

    NSMenu::Run ();

    ObstaclesPositions.clear ();
    Helpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);
}

void Survivor3v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    Helpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
}

bool Survivor3v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    unsigned DeadChaserCount = 0;
    for (unsigned i = 0; i < PlayerLifeStates.size (); ++i)
        if (i != AlonePlayer && !PlayerLifeStates [i])
            ++DeadChaserCount;

    return !PlayerLifeStates [AlonePlayer] || DeadChaserCount == 3;
}

void Survivor3v1::ShowWinScreen (const std::vector< bool >& PlayerLifeStates, std::vector<char> Tokens, vector<unsigned> TurnCounters)
{
    NSMenu::Clear ();

    for (unsigned i = 0; i < 4; ++i)
    {
        stringstream Winner;
        Winner << "Player " << i + 1 << " lasted " << AlonePlayerTurnCounters [i] << " rounds.";
        NSMenu::AddItem(Winner.str());
    }

    NSMenu::Run (true);
}
