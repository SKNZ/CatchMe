#include "GameMode.h"

using namespace Game;

SGameMode Game::MakeGameMode (std::string Name, unsigned PlayerCount,
    FGetSize GetSize,
    FMovePlayer MovePlayer,
    FInitializePlayerPosition InitializePlayerPosition,
    FBuildMatrix BuildMatrix,
    FValidatePlayerPositions ValidatePlayerPositions,
    FIsGameOver IsGameOver)
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