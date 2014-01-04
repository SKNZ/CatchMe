#include "GameMode.h"

using namespace Game;

SGameMode Game::MakeGameMode (std::string Name, unsigned PlayerCount,
    std::function<void (CPosition& Size)> GetSize,
    std::function<void (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)> MovePlayer,
    std::function<void (CPositions& PlayerPositions, const unsigned PlayerCount, const CPosition& Size)> InitializePlayerPosition,
    std::function<void (CMatrix& Matrix, const CPositions& PlayerPositions, const std::vector<bool>& PlayerLifeStates, const char EmptyToken)> BuildMatrix,
    std::function<void (CPositions PlayerPositions, unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates)> ValidatePlayerPositions,
    std::function<bool (const std::vector<bool>& PlayerLifeStates)> IsGameOver)
{
    SGameMode GameMode;

    GameMode.Name                       = Name;
    GameMode.PlayerCount                = PlayerCount;
    GameMode.GetSize                    = GetSize;
    GameMode.MovePlayer                 = MovePlayer;
    GameMode.InitializePlayerPosition   = InitializePlayerPosition;
    GameMode.BuildMatrix                = BuildMatrix;
    GameMode.ValidatePlayerPositions    = ValidatePlayerPositions;
    GameMode.IsGameOver                 = IsGameOver;

    return GameMode;
}