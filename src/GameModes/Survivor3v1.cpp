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
#include <array>

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
} // namespace

void nsSurvivor3v1::GetSize (CPosition& Size)
{
    nsMenu::Clear ();

    nsMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    nsMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    nsMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    nsMenu::Run ();
} // GetSize

void nsSurvivor3v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    nsHelpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
} // MovePlayer

void nsSurvivor3v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    if (CurrentPlayer == AlonePlayer)
    {
		++AlonePlayerTurnCounters [AlonePlayer];
        
        for (unsigned i = 0; i < PlayerPositions.size (); ++i)
            if (PlayerPositions [i] == PlayerPositions [CurrentPlayer] && i != CurrentPlayer)
                PlayerLifeStates [CurrentPlayer] = false;
    }
    else
    {
        if (PlayerPositions [CurrentPlayer] == PlayerPositions [AlonePlayer])
            PlayerLifeStates [AlonePlayer] = false;

        if (PlayerLifeStates [CurrentPlayer] && find (ObstaclesPositions.cbegin(), ObstaclesPositions.cend(), PlayerPositions [CurrentPlayer]) == ObstaclesPositions.cend()) // If Position is not obstacle
            ObstaclesPositions.push_back (PlayerPositions [CurrentPlayer]);
        else
            PlayerLifeStates [CurrentPlayer] = false;
    } // else (not current player)

    int Y = PlayerPositions [CurrentPlayer].first, X = PlayerPositions [CurrentPlayer].second;

    bool SurroundedByObstacles = true;
    std::vector<CPosition> PositionsNearby;

    PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], PlayerMovesY::KStay, PlayerMovesX::KRight));
    PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], PlayerMovesY::KStay, PlayerMovesX::KLeft));
    PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], PlayerMovesY::KUp,   PlayerMovesX::KRight));
    PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], PlayerMovesY::KUp,   PlayerMovesX::KLeft));
    PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], PlayerMovesY::KUp,   PlayerMovesX::KStay));
    PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], PlayerMovesY::KDown, PlayerMovesX::KRight));
    PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], PlayerMovesY::KDown, PlayerMovesX::KLeft));
    PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], PlayerMovesY::KDown, PlayerMovesX::KStay));
    
    for (CPosition Position : PositionsNearby)
        if (Matrix [Position.first] [Position.second] != KTokens [KTokenObstacle])
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
} // BuildMatrix

bool nsSurvivor3v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    unsigned DeadChaserCount = 0;
    for (unsigned i = 0; i < PlayerLifeStates.size (); ++i)
        if (i != AlonePlayer && !PlayerLifeStates [i])
            ++DeadChaserCount;

    return !PlayerLifeStates [AlonePlayer] || DeadChaserCount == 3;
} // IsGameOver

void nsSurvivor3v1::ShowWinScreen (const std::vector< bool >& PlayerLifeStates, const std::vector<char>& Tokens, const vector<unsigned>& TurnCounters)
{
    nsMenu::Clear ();

    vector<pair<unsigned, unsigned>> TurnCounterById;
    for (unsigned i = 0; i < 4; ++i)
        TurnCounterById.push_back (make_pair (i, AlonePlayerTurnCounters [i]));
    
    std::sort (TurnCounterById.begin (), TurnCounterById.end (),
               [] (pair<unsigned, unsigned> a, pair<unsigned, unsigned> b) { return a.second < b.second; });

    for (pair<unsigned, unsigned> TurnCounter : TurnCounterById)
    {
        stringstream Winner;
        Winner << "Player " << KTokens [TurnCounter.first] << " lasted " << TurnCounter.second << " rounds.";
        nsMenu::AddItem(Winner.str());
    }

    nsMenu::Run (true);
} // ShowWinScreen
