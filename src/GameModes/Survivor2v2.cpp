/**
 * @file   Survivor2v2.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Survivor 2v2 game mode
 *
 **/
#include <algorithm>
#include <sstream>

#include "Survivor2v2.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
	nsGame::CPositions ObstaclesPositions;
} // namespace

void nsSurvivor2v2::GetSize (CPosition& Size)
{
    nsMenu::Clear ();

    nsMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    nsMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    nsMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    nsMenu::Run ();
} // GetSize

void nsSurvivor2v2::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    nsHelpers::MovePlayer (Matrix, PlayerPosition, MatrixSize, MoveY, MoveX);
} // MovePlayer

void nsSurvivor2v2::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
    {
        if (i == CurrentPlayer || !PlayerLifeStates[i] || (i + CurrentPlayer) % 2 == 0) // Player 1 & 3 and 2 & 4 are teamed up.
            continue;

        if (PlayerPositions [CurrentPlayer] == PlayerPositions [i])
        {
            PlayerLifeStates[i] = false;

            CPositions::iterator Iterator = find (ObstaclesPositions.begin (), ObstaclesPositions.end (), PlayerPositions [i]);
            if (Iterator != ObstaclesPositions.end ())
                ObstaclesPositions.erase (Iterator);
        }
    } // foreach (player)

    for (CPosition Position : ObstaclesPositions)
            if (PlayerPositions [CurrentPlayer] == Position)
                PlayerLifeStates [CurrentPlayer] = false;

    if(PlayerLifeStates [CurrentPlayer] && find (ObstaclesPositions.cbegin(), ObstaclesPositions.cend(), PlayerPositions [CurrentPlayer]) == ObstaclesPositions.cend())
        ObstaclesPositions.push_back (PlayerPositions [CurrentPlayer]);
} // ValidatePlayerPositions

void nsSurvivor2v2::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
    PlayerPositions [1] = { 0, 0 }; // Top left
    PlayerPositions [2] = { MaxSize.first - 1, 0 }; // Bottom left
    PlayerPositions [3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right

    ObstaclesPositions.clear ();
    nsHelpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);

    nsMenu::Clear ();

    nsMenu::AddItem ("The players 1 and 3 form a team against the players 2 and 4.");

    nsMenu::Run ();
} // InitializeRound

void nsSurvivor2v2::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    nsHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
} // BuildMatrix

bool nsSurvivor2v2::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    return (!PlayerLifeStates[0] && !PlayerLifeStates[2]) || (!PlayerLifeStates[1] && !PlayerLifeStates[3]);
} // IsGameOver

void nsSurvivor2v2::ShowWinScreen (const std::vector< bool >& PlayerLifeStates, const std::vector<char>& Tokens, const vector<unsigned>& TurnCounters)
{
    nsMenu::Clear ();

    for (unsigned i = 0; i < 4; ++i)
    {
        if (PlayerLifeStates [i])
        {
            stringstream Winner;
            Winner << "Player " << i + 1 << " lasted " << TurnCounters [i] << " rounds.";
            Winner << "Player " << ((i + 2) % 2) + 1 << " lasted " << TurnCounters [(i + 2) % 2] << " rounds.";
            nsMenu::AddItem(Winner.str());
            break;
        }
    }

    nsMenu::Run (true);
} // ShowWinScreen
