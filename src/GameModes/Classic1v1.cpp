#include "Classic1v1.h"

#include "../Game.h"

using namespace std;

/**
 *
 * @todo Add a menu here, that allows the palyer to selection the size of the grid he wants to play on.
 * 
 **/
void Classic1v1::GetSize (CPosition& Size)
{
    Size = { 10, 20 };
}

void Classic1v1::MovePlayer (CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesX MoveX, const PlayerMovesY MoveY)
{
    int DiffX = static_cast<int> (MoveX);
    int DiffY = static_cast<int> (MoveY);
    
    if (PlayerPosition.first + DiffX > 0 && PlayerPosition.first + DiffX < MatrixSize.first - 1)
        PlayerPosition.first += DiffX;

    if (PlayerPosition.second + DiffY > 0 && PlayerPosition.second + DiffY < MatrixSize.second - 1)
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
                PlayerPositions [0] = { 0, MaxSize.second - 1 }; // Top right
                break;
            case 1:
                PlayerPositions [1] = { MaxSize.first - 1, 0 }; // Bottom left
                break;
        }
    }
}

void Classic1v1::BuildMatrix (CMatrix& Matrix, const CPositions& PlayerPositions, const char EmptyToken)
{
    for (CLine& Line : Matrix)
        fill (Line.begin (), Line.end (), EmptyToken);

    for (unsigned i = 0; i < PlayerPositions.size (); ++i)
        Matrix  [PlayerPositions [i].first] [PlayerPositions [i].second] = Game::KTokens [i];
}
