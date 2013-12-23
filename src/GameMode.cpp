#include "GameMode.h"

using namespace Game;

SGameMode Game::MakeGameMode (std::string Name, unsigned PlayerCount,
    std::function<void (CPosition& Size)> GetSize,
    std::function<void (CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesX MoveX, const PlayerMovesY MoveY)> MovePlayer,
    std::function<void (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& Size)> InitializePlayerPosition,
    std::function<void (CMatrix& Matrix, const CPositions& PlayerPositions, const char EmptyToken)> BuildMatrix)
{
    SGameMode GameMode;

    GameMode.Name                       = Name;
    GameMode.PlayerCount                = PlayerCount;
    GameMode.GetSize                    = GetSize;
    GameMode.MovePlayer                 = MovePlayer;
    GameMode.InitializePlayerPosition   = InitializePlayerPosition;
    GameMode.BuildMatrix                = BuildMatrix;

    return GameMode;
}