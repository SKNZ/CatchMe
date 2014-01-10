/**
 * @author F. Narenji
 *
 * @date   19/12/2013
 *
 * @brief  Game implementation, movement, render matrix, main loop
 *
**/
#include <iostream>
#include <sstream>
#include <thread>
#include <cstdlib>

#include "Menu.h"
#include "Game.h"
#include "GameUI.h"
#include "Config.h"
#include "Console.h"
#include "Network.h"

using namespace std;

namespace
{
    using namespace Game;

    /**
     *
     * @brief Game mode selection screen
     *
     **/
    void GetGameMode (SGameMode& GameMode)
    {
        Menu::Clear ();

        for (SGameMode CurrentGameMode : KGameModes)
            Menu::AddItem (CurrentGameMode.Name, [&GameMode, CurrentGameMode] () { GameMode = CurrentGameMode; });

        Menu::AddItem("Quitter", [] () { exit(0); });

        Menu::Run ();
    }

    void MovementHandler (int Action, const CMatrix& Matrix, CPositions& PlayerPositions, const unsigned CurrentPlayer, const CPosition& Size, const SGameMode& GameMode)
    {
        CPosition& PlayerPosition = PlayerPositions [CurrentPlayer];

        switch (Action)
        {
            case 0: // Up & left
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KUp, PlayerMovesX::KLeft);
                break;
            case 1: // Up
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KUp, PlayerMovesX::KStay);
                break;
            case 2: // Up & right
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KUp, PlayerMovesX::KRight);
                break;
            case 3: // Left
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KStay, PlayerMovesX::KLeft);
                break;
            case 4: // Stay
                return; // Having a Stay move has been found to flaw the gameplay.
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KStay, PlayerMovesX::KStay);
                break;
            case 5: // Right
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KStay, PlayerMovesX::KRight);
                break;
            case 6: // Down & left
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KDown, PlayerMovesX::KLeft);
                break;
            case 7: // Down
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KDown, PlayerMovesX::KStay);
                break;
            case 8: // Down & right
                GameMode.MovePlayer (Matrix, PlayerPosition, Size, PlayerMovesY::KDown, PlayerMovesX::KRight);
                break;
        }
    }
}

int Game::Run ()
{
    Console::DisableCanonicalInputMode ();
    Config::LoadFile ();

    for (;;)
    {
        SGameMode        GameMode;
        CPosition        Size;
        vector<bool>     PlayerLifeStates;
        vector<unsigned> TurnCounters;

        GetGameMode (GameMode);
        GameMode.GetSize (Size);
        
        Network::AwaitConnections (GameMode.PlayerCount);
        
        for (unsigned i = 0; i < GameMode.RoundCount; ++i)
        {
            CPositions      PlayerPositions;
            unsigned        CurrentPlayer = 0; // Whose turn it is
            CMatrix         Matrix;

            PlayerLifeStates.resize (GameMode.PlayerCount, true);
            TurnCounters.resize (GameMode.PlayerCount, 0);

            Matrix.resize (Size.first);
 
            for (CLine& Line : Matrix)
                Line.resize (Size.second);

            GameMode.InitializeRound (PlayerPositions, GameMode.PlayerCount, Size);

            GameMode.BuildMatrix (Matrix, PlayerPositions, PlayerLifeStates, KTokens [KTokenEmpty]);

            for (;;)
            {
                this_thread::sleep_for (std::chrono::milliseconds (Config::RenderLoopInterval)); // Render loop interval

                UI::ShowMatrix (Matrix);
                UI::ShowControls (CurrentPlayer);

                if (GameMode.IsGameOver (PlayerLifeStates))
                    break;

                if (PlayerLifeStates [CurrentPlayer])
                {
                    size_t Action = 0;

                    if (Console::WaitForKeyPress (Config::TurnTimeoutDelay))
                    {
                        char Opcode = tolower (cin.get ());

                        Action = KControlsByToken.at (KTokens.at (CurrentPlayer)).find (Opcode);
                        if (Action == string::npos || Action == 4) // 4 is the position of the middle key (such as S or 5). We do not want it.
                        {
                            cout << "The key you entered wasn't valid." << endl;
                            Console::WaitForKeyPress (Config::ErrorMessageDisplayTime); // Wait a defined amount of time for the message to be shown.

                            continue; // The player failed. Let's render the grid again and ask him once more.
                        }
                    }
                    else
                    {
                        srand (time(NULL));

                        Action = rand () % 8;
                    }

                    MovementHandler (Action, Matrix, PlayerPositions, CurrentPlayer, Size, GameMode);

                    GameMode.ValidatePlayerPositions (PlayerPositions, CurrentPlayer, PlayerLifeStates);

                    GameMode.BuildMatrix (Matrix, PlayerPositions, PlayerLifeStates, KTokens [KTokenEmpty]);
                }

                ++TurnCounters [CurrentPlayer];
                ++CurrentPlayer;
                if (CurrentPlayer >= GameMode.PlayerCount)
                    CurrentPlayer = 0;
            }
        }

        GameMode.ShowWinScreen (PlayerLifeStates, KTokens, TurnCounters);
    }

    return 0;
}