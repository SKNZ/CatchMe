/**
 * @file   Bot.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Bot logic
 *
 **/
#include <cmath>
#include <algorithm>
#include <iostream>

#include "Bot.h"
#include "Game.h"
#include "GameModes/Helpers.h"

namespace
{
    using namespace nsGame;

    /**
     * 
     * @brief Check if a player is within one case of distance and attack if yes.
     * 
     * @return Whether a kill was made or not.
     * 
     **/
    bool CheckForPlayerInRangeAndAttack (const CMatrix& Matrix, const std::vector<bool>& PlayerLifeStates, CPositions& PlayerPositions, unsigned CurrentPlayer, PlayerMovesY MoveY, PlayerMovesX MoveX)
    {
        CPosition Position = nsHelpers::MakePosition (Matrix, PlayerPositions [CurrentPlayer], MoveY, MoveX);
        
        for (unsigned i = KTokenPlayer1; i < KTokenPlayer4; ++i) // Check if the Token at the position is a player token
            if (Matrix [Position.first] [Position.second] == KTokens [i] && i != CurrentPlayer && PlayerLifeStates[i])
            {
                PlayerPositions [CurrentPlayer] = Position;
                return true;
            }

        return false;
    } // CheckForPlayerInRangeAndAttack

    /**
     * 
     * @brief Calculates the distances between two points of the grid.
     * 
     **/
    unsigned FindDistance (CPosition From, CPosition To)
    {
        int DeltaX = From.first - To.first;
        int DeltaY = From.second - To.second;
        
        DeltaX *= DeltaX;
        DeltaY *= DeltaY;
        
        return unsigned (sqrt (DeltaX + DeltaY));
    } // FindDistance

    /**
     * 
     * @brief Returns the position of the nearest player.
     * 
     **/
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
            } // if (alive && not us)

        return PlayerPositions [NearestPlayerPositionIndex];
    } // FindNearestPlayerPosition

    /**
     * 
     * @brief Uses a simplified implementation of the A* (all movements of the same cost) algorithm to find
     *          the next movement of the bot by evaluating the distance between each of the nearby
     *          spots to the target position.
     * 
     **/
    CPosition FindNextMove (const CMatrix& Matrix, CPosition CurrentPosition, CPosition Target)
    {
        std::vector<CPosition> PositionsNearby;

        PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, CurrentPosition, PlayerMovesY::KStay, PlayerMovesX::KRight));
        PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, CurrentPosition, PlayerMovesY::KStay, PlayerMovesX::KLeft));
        PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, CurrentPosition, PlayerMovesY::KUp,   PlayerMovesX::KRight));
        PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, CurrentPosition, PlayerMovesY::KUp,   PlayerMovesX::KLeft));
        PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, CurrentPosition, PlayerMovesY::KUp,   PlayerMovesX::KStay));
        PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, CurrentPosition, PlayerMovesY::KDown, PlayerMovesX::KRight));
        PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, CurrentPosition, PlayerMovesY::KDown, PlayerMovesX::KLeft));
        PositionsNearby.push_back (nsHelpers::MakePosition (Matrix, CurrentPosition, PlayerMovesY::KDown, PlayerMovesX::KStay));

        std::sort (PositionsNearby.begin (), PositionsNearby.end (), [Target] (CPosition a, CPosition b) { return FindDistance (a, Target) < FindDistance (b, Target); });

        return PositionsNearby [0];
    } // FindNextMove
} // namespace

void nsGame::nsBot::MakeMove (const CMatrix& Matrix, const std::vector<bool>& PlayerLifeStates, CPositions& PlayerPositions, unsigned CurrentPlayer)
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
} // MakeMove
