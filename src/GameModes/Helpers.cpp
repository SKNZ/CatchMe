#include "Helpers.h"

using namespace Game;

void Helpers::MovePlayer (CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    int DiffX = static_cast<int> (MoveX);
    int DiffY = static_cast<int> (MoveY);
    
    if (PlayerPosition.first + DiffY >= 0 && PlayerPosition.first + DiffY < MatrixSize.first)
        PlayerPosition.first += DiffY;

    if (PlayerPosition.second + DiffX >= 0 && PlayerPosition.second + DiffX < MatrixSize.second)
        PlayerPosition.second += DiffX;
}
