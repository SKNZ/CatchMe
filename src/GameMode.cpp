/**
 * @file   GameMode.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  SGameMode constructor implementation
 *
 **/
#include "GameMode.h"

using namespace NSGame;

SGameMode NSGame::MakeGameMode (std::string Name, unsigned PlayerCount, unsigned RoundCount, bool AllowStay,
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
    GameMode.AllowStay                  = AllowStay;
    GameMode.GetSize                    = GetSize;
    GameMode.MovePlayer                 = MovePlayer;
    GameMode.InitializeRound   = InitializeRound;
    GameMode.BuildMatrix                = BuildMatrix;
    GameMode.ValidatePlayerPositions    = ValidatePlayerPositions;
    GameMode.IsGameOver                 = IsGameOver;
    GameMode.ShowWinScreen              = ShowWinScreen;

    return GameMode;
}
