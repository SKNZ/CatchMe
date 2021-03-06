/**
 * @file   MapEditor.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Map editor for obstacles
 *
 **/
#include <fstream>
#include <sstream>
#include <algorithm>

#include "MapEditor.h"
#include "Helpers.h"

#include "../Game.h"
#include "../Menu.h"

using namespace std;

namespace
{
    nsGame::CPositions ObstaclesPositions;
} // namespace

void nsMapEditor::GetSize (CPosition& Size)
{
    nsMenu::Clear ();

    nsMenu::AddItem ("Small map", [&Size] () { Size = { 5, 10 }; });
    nsMenu::AddItem ("Medium map", [&Size] () { Size = { 10, 20 }; });
    nsMenu::AddItem ("Great map", [&Size] () { Size = { 20, 40 }; });

    nsMenu::Run ();
} // GetSize

void nsMapEditor::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    int DiffY = static_cast<int> (MoveY);
    int DiffX = static_cast<int> (MoveX);
    
    if (0 == DiffX && 0 == DiffY) // Stay case, used for add/remove obstacles
    {
        CPositions::iterator Iterator = find (ObstaclesPositions.begin (), ObstaclesPositions.end (), make_pair(PlayerPosition.first + DiffY, PlayerPosition.second + DiffX));

        if (Iterator == ObstaclesPositions.end ())
            ObstaclesPositions.push_back (PlayerPosition);
        else ObstaclesPositions.erase (Iterator);

        return;
    } // if (stay)

    if (PlayerPosition.first + DiffY < 0 || PlayerPosition.first + DiffY >= MatrixSize.first)
        DiffY = 0;

    if (PlayerPosition.second + DiffX < 0 || PlayerPosition.second + DiffX >= MatrixSize.second)
        DiffX = 0;

    PlayerPosition.first += DiffY;
    PlayerPosition.second += DiffX;
} // MovePlayer

void nsMapEditor::ValidatePlayerPositions (const CMatrix& Matrix, const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
    if (PlayerPositions [CurrentPlayer] == make_pair (0, 0)) // The map editor quits if the player is back to its original position
        PlayerLifeStates [CurrentPlayer] = false;
} // ValidatePlayerPositions

void nsMapEditor::InitializeRound (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    PlayerPositions [0] = { 0, 0 }; // Top right

    ObstaclesPositions.clear ();
    nsHelpers::LoadObstaclesFromFile (ObstaclesPositions, MaxSize);

    nsMenu::Clear ();
    nsMenu::AddItem ("To add or remove an obstacle use the 'S' key.");
    nsMenu::AddItem ("To quit, you must go the top left square.");
    nsMenu::Run ();
} // InitializeRound

void nsMapEditor::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const vector<bool>& PlayerLifeStates, const char EmptyToken)
{
    nsHelpers::AddObstaclesAndPlayersToMatrix (Matrix, PlayerPositions, PlayerLifeStates, ObstaclesPositions, EmptyToken);
    
    std::stringstream FileName;
    FileName << "./" << Matrix.size () << "_" << Matrix.begin ()->size () << ".map";

    std::ofstream File (FileName.str ());

    if (!File)
    {
        return;
        throw std::runtime_error("There was an error trying to open the file: " + FileName.str ());
    } // if (file not exist)
    
    for (CPosition Obstacle : ObstaclesPositions)
        if (Obstacle != make_pair (0, 0) && Obstacle != make_pair (0, int (Matrix.begin ()->size () -1)) // No spawn points
        && Obstacle != make_pair (int (Matrix.size ()), int (Matrix.begin ()->size () - 1)) && Obstacle != make_pair (int (Matrix.size ()), 0))
            File << Obstacle.first << " " << Obstacle.second << endl;
} // BuildMatrix

bool nsMapEditor::IsGameOver (const vector<bool>& PlayerLifeStates)
{
    return !PlayerLifeStates [0];
} // IsGameOver

void nsMapEditor::ShowWinScreen (const std::vector<bool>& PlayerLifeStates, const std::vector<char>& Tokens, const std::vector<unsigned>& TurnCounters)
{
} // ShowWinScreen
