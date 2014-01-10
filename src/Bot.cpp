#include <cmath>
#include <algorithm>
#include <iostream>

#include "Bot.h"
#include "Game.h"

namespace
{
    using namespace Game;

    CPosition MakePosition (const CMatrix& Matrix, CPosition Position, PlayerMovesY MoveY, PlayerMovesX MoveX)
    {
        int Y = Position.first;
        int X = Position.second;

        Y += static_cast<int> (MoveY);
        X += static_cast<int> (MoveX);
        
        if (Y < 0 || X < 0 || Y >= Matrix.size () ||  X >= Matrix.begin ()->size () || Matrix [Y] [X] == KTokens [KTokenObstacle]) // Out of bounds or obstacle
            return Position; // Return the initial position

        return { Y, X };
    }
    
    bool CheckForPlayerInRangeAndAttack (const CMatrix& Matrix, const std::vector<bool>& PlayerLifeStates, CPositions& PlayerPositions, unsigned CurrentPlayer, PlayerMovesY MoveY, PlayerMovesX MoveX)
    {
        CPosition Position = MakePosition (Matrix, PlayerPositions [CurrentPlayer], MoveY, MoveX);
        
        for (unsigned i = KTokenPlayer1; i < KTokenPlayer4; ++i) // Check if the Token at the position is a player token
            if (Matrix [Position.first] [Position.second] == KTokens [i] && i != CurrentPlayer && PlayerLifeStates[i])
            {
                PlayerPositions [CurrentPlayer] = Position;
                return true;
            }

        return false;
    }

    unsigned FindDistance (CPosition From, CPosition To)
    {
        int DeltaX = From.first - To.first;
        int DeltaY = From.second - To.second;
        
        DeltaX *= DeltaX;
        DeltaY *= DeltaY;
        
        return unsigned (sqrt (DeltaX + DeltaY));
    }
    
    CPosition FindNearestPlayerPosition (const std::vector<bool>& PlayerLifeStates, const CPositions& PlayerPositions, unsigned CurrentPlayer)
    {
        unsigned NearestPlayerPositionIndex = 0;
        unsigned NearestPlayerDistance = 0;

        for (unsigned i = 0; i < PlayerPositions.size (); ++i)
            if (i != CurrentPlayer && PlayerLifeStates[i])
            {
                unsigned Distance = FindDistance (PlayerPositions [i], PlayerPositions [CurrentPlayer]);
                
                if (0 == NearestPlayerDistance || Distance < NearestPlayerDistance)
                {
                    NearestPlayerDistance = Distance;
                    NearestPlayerPositionIndex = i;
                }
            }

        return PlayerPositions [NearestPlayerPositionIndex];
    }

    CPosition FindNextMove (const CMatrix& Matrix, CPosition CurrentPosition, CPosition Target)
    {
        std::vector<CPosition> PositionsNearby;

        PositionsNearby.push_back (MakePosition (Matrix, CurrentPosition, PlayerMovesY::KStay, PlayerMovesX::KRight));
        PositionsNearby.push_back (MakePosition (Matrix, CurrentPosition, PlayerMovesY::KStay, PlayerMovesX::KLeft));
        PositionsNearby.push_back (MakePosition (Matrix, CurrentPosition, PlayerMovesY::KUp,   PlayerMovesX::KRight));
        PositionsNearby.push_back (MakePosition (Matrix, CurrentPosition, PlayerMovesY::KUp,   PlayerMovesX::KLeft));
        PositionsNearby.push_back (MakePosition (Matrix, CurrentPosition, PlayerMovesY::KUp,   PlayerMovesX::KStay));
        PositionsNearby.push_back (MakePosition (Matrix, CurrentPosition, PlayerMovesY::KDown, PlayerMovesX::KRight));
        PositionsNearby.push_back (MakePosition (Matrix, CurrentPosition, PlayerMovesY::KDown, PlayerMovesX::KLeft));
        PositionsNearby.push_back (MakePosition (Matrix, CurrentPosition, PlayerMovesY::KDown, PlayerMovesX::KStay));

        std::sort (PositionsNearby.begin (), PositionsNearby.end (), [Target] (CPosition a, CPosition b) { return FindDistance (a, Target) < FindDistance (b, Target); });

        return PositionsNearby [0];
    }
}

void Game::Bot::MakeMove (const CMatrix& Matrix, const std::vector<bool>& PlayerLifeStates, CPositions& PlayerPositions, unsigned CurrentPlayer)
{
    // Check if a there is a player in attack range, and kill him.
    bool HasKilledSomeOne = CheckForPlayerInRangeAndAttack (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer, PlayerMovesY::KStay,   PlayerMovesX::KRight)
                || CheckForPlayerInRangeAndAttack (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer, PlayerMovesY::KUp,     PlayerMovesX::KRight)
                || CheckForPlayerInRangeAndAttack (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer, PlayerMovesY::KUp,     PlayerMovesX::KStay)
                || CheckForPlayerInRangeAndAttack (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer, PlayerMovesY::KUp,     PlayerMovesX::KLeft)
                || CheckForPlayerInRangeAndAttack (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer, PlayerMovesY::KStay,   PlayerMovesX::KLeft)
                || CheckForPlayerInRangeAndAttack (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer, PlayerMovesY::KDown,   PlayerMovesX::KLeft)
                || CheckForPlayerInRangeAndAttack (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer, PlayerMovesY::KDown,   PlayerMovesX::KStay)
                || CheckForPlayerInRangeAndAttack (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer, PlayerMovesY::KDown,   PlayerMovesX::KRight);

    if (HasKilledSomeOne) // We already made our move. No more reason to play.
        return;

    CPosition TargetPosition = FindNearestPlayerPosition (PlayerLifeStates, PlayerPositions, CurrentPlayer);

    CPosition NextMove = FindNextMove (Matrix, PlayerPositions [CurrentPlayer], TargetPosition);    

    PlayerPositions [CurrentPlayer] = NextMove;
}