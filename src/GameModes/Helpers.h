#pragma once

#include "../Game.h"

namespace Helpers
{
    void MovePlayer (Game::CPosition& PlayerPosition, const Game::CPosition& MatrixSize, const Game::PlayerMovesY MoveY, const Game::PlayerMovesX MoveX);
}