#include "Classic1v1.h"

#include <iostream>
#include <ncurses.h>
#include "../Game.h"

using namespace std;

void Classic1v1::GetSize (CPosition& Size)
{
    Size = { 10, 20 };
}

void Classic1v1::MovePlayer (CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesX MoveX, const PlayerMovesY MoveY)
{
    bool hardWalls = true;

    int DiffX = static_cast<int> (MoveX);
    int DiffY = static_cast<int> (MoveY);
    
    // Make him pop on the other side if he leaves the boundaries
    if (PlayerPosition.first + DiffX < 0)
        if (!hardWalls)
            PlayerPosition.first = MatrixSize.first - 1; 
        else beep();
    else if (PlayerPosition.first + DiffX > MatrixSize.first - 1)
        if (!hardWalls)
            PlayerPosition.first = 0;
        else beep();
    else
        PlayerPosition.first += DiffX;

    if (PlayerPosition.second + DiffY < 0)
        if (!hardWalls)
            PlayerPosition.second = MatrixSize.second - 1;
        else beep();
    else if (PlayerPosition.second + DiffY > MatrixSize.second - 1)
        if (!hardWalls)
            PlayerPosition.second = 0;
        else beep();
    else
        PlayerPosition.second += DiffY;
}

void Classic1v1::InitializePlayerPositions (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& MaxSize)
{
    PlayerPositions.resize (PlayerCount);

    for (unsigned i = 0; i < PlayerCount; ++i)
    {
        switch (i)
        {
            case 0:
                PlayerPositions[0] = { 0, MaxSize.second - 1 }; // Top right
                break;
            case 1:
                PlayerPositions[1] = { MaxSize.first - 1, 0 }; // Bottom left
                break;
            case 2:
                PlayerPositions[2] = { 0, 0 }; // Top left
                break;
            case 3:
                PlayerPositions[3] = { MaxSize.first - 1, MaxSize.second - 1 }; // Bottom right
                break;
        }
    }
}

void Classic1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const char EmptyToken)
{
    for (CLine& Line : Matrix)
        fill (Line.begin (), Line.end (), EmptyToken);

    for (unsigned i = 0; i < PlayerPositions.size(); ++i)
        Matrix  [PlayerPositions[i].first] [PlayerPositions[i].second] = Game::KTokens [i];
}
