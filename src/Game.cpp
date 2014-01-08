/**
 * @author F. Narenji
 *
 * @date   19/12/2013
 *
 * @brief  Game implementation, movement, render matrix, main loop
 *
**/
#include <iostream>
#include <thread>

#include "Menu.h"
#include "Game.h"
#include "GameUI.h"
#include "Config.h"

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
    
    cout << Config::ErrorMessageDisplayTime << endl << Config::RenderLoopInterval << endl;
    cin.get();

    for (;;)
    {
        SGameMode       GameMode;
        CPositions      PlayerPositions;
        CPosition       Size;
        unsigned        CurrentPlayer = 0; // Whose turn it is
        CMatrix         Matrix;
        vector<bool>    PlayerLifeStates;

        GetGameMode (GameMode);
        GameMode.GetSize (Size);
            
        PlayerLifeStates.resize (GameMode.PlayerCount, true);

        Matrix.resize (Size.first);

        for (CLine& Line : Matrix)
            Line.resize (Size.second);

        GameMode.InitializePlayerPosition (PlayerPositions, GameMode.PlayerCount, Size);

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
                if (Console::WaitForKeyPress (15000))
                {
                    char Opcode = cin.get ();

                    size_t Action = KControlsByToken.at (KTokens.at (CurrentPlayer)).find (Opcode);

                    if (Action == string::npos)
                    {
                        cout << "The key you entered wasn't valid." << endl;
                        Console::WaitForKeyPress(Config::ErrorMessageDisplayTime); // Wait a defined amount of time for the message to be shown.

                        continue; // The player failed. Let's render the grid again and ask him once more.
                    }

                    MovementHandler (Action, Matrix, PlayerPositions, CurrentPlayer, Size, GameMode);

                    GameMode.ValidatePlayerPositions (PlayerPositions, CurrentPlayer, PlayerLifeStates);
                }

                GameMode.BuildMatrix (Matrix, PlayerPositions, PlayerLifeStates, KTokens [KTokenEmpty]);
            }

            CurrentPlayer++;
            if (CurrentPlayer >= GameMode.PlayerCount)
                CurrentPlayer = 0;
        }

        Console::ClearScreen();

        for (unsigned i = 0; i < GameMode.PlayerCount; ++i)
            if (PlayerLifeStates [i])
                cout << "The game is over. The player " << i << " playing as '" << KTokens [i] << "' won." << endl;

        cin.get();
    }

    return 0;
}