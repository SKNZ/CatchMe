#include "GameMode.h"

using namespace Game;

SGameMode Game::MakeGameMode (std::string Name, unsigned PlayerCount, unsigned RoundCount,
    FGetSize GetSize,
    FMovePlayer MovePlayer,
    FInitializeRound InitializeRound,
    FBuildMatrix BuildMatrix,
    FValidatePlayerPositions ValidatePlayerPositions,
    FIsGameOver IsGameOver,
    FShowWinScreen ShowWinScreen)
{
    SGameMode GameMode;

    GameMode.Name                       = Name;
    GameMode.PlayerCount                = PlayerCount;
    GameMode.RoundCount                 = RoundCount;
    GameMode.GetSize                    = GetSize;
    GameMode.MovePlayer                 = MovePlayer;
    GameMode.InitializeRound   = InitializeRound;
    GameMode.BuildMatrix                = BuildMatrix;
    GameMode.ValidatePlayerPositions    = ValidatePlayerPositions;
    GameMode.IsGameOver                 = IsGameOver;
    GameMode.ShowWinScreen              = ShowWinScreen;

    return GameMode;
}
