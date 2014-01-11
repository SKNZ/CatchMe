/**
 * @file   Survivor3v1.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Survivor 3v1 game mode
 *
 **/
#include <algorithm>
#include <sstream>

#include "Survivor3v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
	nsGame::CPositions ObstaclesPositions;
    array<unsigned, 4> AlonePlayerTurnCounters;

    int AlonePlayer = -1;
}

void nsSurvivor3v1::GetSize (CPosition& Size)
{
    nsMenu::Clear ();

    nsMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    nsMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    nsMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    nsMenu::Run ();
}

void nsSurvivor3v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    nsHelpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
}

void nsSurvivor3v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    if (CurrentPlayer == AlonePlayer)
    {
		AlonePlayerTurnCounters [AlonePlayer]++;
    }
    else
    {
        if (PlayerPositions [CurrentPlayer] == PlayerPositions [AlonePlayer])
            PlayerLifeStates [AlonePlayer] = false;

        if (PlayerLifeStates [CurrentPlayer] && find (ObstaclesPositions.cbegin(), ObstaclesPositions.cend(), PlayerPositions [CurrentPlayer]) == ObstaclesPositions.cend()) // If Position is not obstacle
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
} // ValidatePlayerPositions

void nsSurvivor3v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
    PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
    PlayerPositions [2] = { 0, 0 }; // Top left
    PlayerPositions [3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right

    ++AlonePlayer;

    nsMenu::Clear ();

    std::stringstream Text;
    Text << "The lone player is '" << KTokens [AlonePlayer] << "'.";
    nsMenu::AddItem (Text.str ());

    nsMenu::Run ();

    ObstaclesPositions.clear ();
    nsHelpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);
    
    if (*AlonePlayerTurnCounters.crbegin() != 0) // If each player has played its turn, reset all state if they want to replay the round.
    {
        fill (AlonePlayerTurnCounters.begin (), AlonePlayerTurnCounters.end (), 0);
        AlonePlayer = 0;
    }
} // InitializeRound

void nsSurvivor3v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    nsHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
}

bool nsSurvivor3v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    unsigned DeadChaserCount = 0;
    for (unsigned i = 0; i < PlayerLifeStates.size (); ++i)
        if (i != AlonePlayer && !PlayerLifeStates [i])
            ++DeadChaserCount;

    return !PlayerLifeStates [AlonePlayer] || DeadChaserCount == 3;
}

void nsSurvivor3v1::ShowWinScreen (const std::vector< bool >& PlayerLifeStates, const std::vector<char>& Tokens, const vector<unsigned>& TurnCounters)
{
    nsMenu::Clear ();

    for (unsigned i = 0; i < 4; ++i)
    {
        stringstream Winner;
        Winner << "Player " << i + 1 << " lasted " << AlonePlayerTurnCounters [i] << " rounds.";
        nsMenu::AddItem(Winner.str());
    }

    nsMenu::Run (true);
} // ShowWinScreen
