/**
 * @file   Classic3v1.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Classic 3v1 game mode
 *
 **/
#include <sstream>
#include <array>

#include "Classic3v1.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
    nsGame::CPositions ObstaclesPositions;
    
    /**
     * 
     * @brief The numbers of turns each alone player survived.
     * 
     */
    std::array<unsigned, 4> AlonePlayerTurnCounters;

    int AlonePlayer = -1;
} // namespace

void nsClassic3v1::GetSize (CPosition& Size)
{
    nsMenu::Clear ();

    nsMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    nsMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    nsMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    nsMenu::Run ();
} // GetSize

void nsClassic3v1::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    nsHelpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
} // MovePlayer

void nsClassic3v1::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions,
                                            unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates)
{
    if (PlayerPositions [CurrentPlayer] == PlayerPositions [AlonePlayer] && CurrentPlayer != AlonePlayer)
        PlayerLifeStates [AlonePlayer] = false;

	if (CurrentPlayer == AlonePlayer)
    {
		AlonePlayerTurnCounters[AlonePlayer]++;
        
        for (unsigned i = 0; i < PlayerPositions.size (); ++i)
            if (PlayerPositions [i] == PlayerPositions [CurrentPlayer] && i != CurrentPlayer)
                PlayerLifeStates [CurrentPlayer] = false;
    }
} // ValidatePlayerPositions

void nsClassic3v1::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
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

    // If each player has played its turn, reset all state if they want to replay the same game mode.
    if (*AlonePlayerTurnCounters.crbegin() != 0)
    {
        fill (AlonePlayerTurnCounters.begin (), AlonePlayerTurnCounters.end (), 0);
        AlonePlayer = 0;
    } // if (everyone played)
} // InitializeRound

void nsClassic3v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    nsHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
} // BuildMatrix

bool nsClassic3v1::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    unsigned DeadChaserCount = 0;
    for (unsigned i = 0; i < PlayerLifeStates.size (); ++i)
        if (i != AlonePlayer && !PlayerLifeStates [i])
            ++DeadChaserCount;

    return !PlayerLifeStates [AlonePlayer];
} // IsGameOver

void nsClassic3v1::ShowWinScreen (const std::vector<bool>& PlayerLifeStates, const std::vector<char>& Tokens, const vector<unsigned>& TurnCounters)
{
    nsMenu::Clear ();

    for (unsigned i = 0; i < 4; ++i)
    {
        stringstream Winner;
        Winner << "Player " << i + 1 << " lasted " << AlonePlayerTurnCounters [i] << " rounds.";
        nsMenu::AddItem(Winner.str() );
    }

    nsMenu::Run (true);
} // ShowWinScreen
