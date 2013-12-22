/**
 * @author F. Narenji
 *
 * @date   19/12/2013
 *
 * @brief  Game implementation, movement, render matrix, main loop
 *
**/
#include "Menu.h"
#include "Game.h"
#include "GameUI.h"

#include <iostream>
#include <limits>
#include <thread>
#include <ncurses.h>

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
        Menu::Clear();
        for (SGameMode CurrentGameMode : KGameModes)
            Menu::AddItem(CurrentGameMode.Name, [&GameMode, CurrentGameMode]() { GameMode = CurrentGameMode; });
        Menu::Run();
    }
    
    bool MovementHandler(CPositions& PlayerPositions, const unsigned CurrentPlayer, const CPosition& Size, const SGameMode& GameMode)
    {
        char Opcode = cin.get ();

        size_t Action = KControlsByToken.at (KTokens.at (CurrentPlayer)).find(Opcode);

        if (Action == string::npos)
        {
            cout << "The key you entered wasn't valid." << endl;
            this_thread::sleep_for (KErrorMessageDisplayTime); // Wait a defined amount of time for the message to be shown.
            return false; // The player failed. Let's render the grid again and ask him once more.
        }
        CPosition& PlayerPosition = PlayerPositions[CurrentPlayer];

        switch (Action)
        {
            case 0: // Up & left
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KUp, PlayerMovesY::KLeft);
                break;
            case 1: // Up
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KUp, PlayerMovesY::KStay);
                break;
            case 2: // Up & right
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KUp, PlayerMovesY::KRight);
                break;
            case 3: // Left
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KStay, PlayerMovesY::KLeft);
                break;
            case 4: // Stay
                return false; // Having a Stay move has been found to flaw the gameplay.
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KStay, PlayerMovesY::KStay);
                break;
            case 5: // Right
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KStay, PlayerMovesY::KRight);
                break;
            case 6: // Down & left
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KDown, PlayerMovesY::KLeft);
                break;
            case 7: // Down
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KDown, PlayerMovesY::KStay);
                break;
            case 8: // Down & right
                GameMode.MovePlayer (PlayerPosition, Size, PlayerMovesX::KDown, PlayerMovesY::KRight);
                break;
        }

        return true;
    }
}

int Game::Run ()
{
    SGameMode   GameMode;
    CPositions  PlayerPositions;
    CPosition   Size;
    unsigned    CurrentPlayer = 0; // Whose turn it is
    CMatrix     Matrix;

    Console::DisableCanonicalInputMode ();

    GetGameMode (GameMode);
    GameMode.GetSize(Size);

    Matrix.resize (Size.first);

    for (CLine& Line : Matrix)
        Line.resize (Size.second);

    GameMode.InitializePlayerPosition(PlayerPositions, GameMode.PlayerCount, Size);
    GameMode.BuildMatrix(Matrix, PlayerPositions, (*KTokens.rbegin ()));

    for (;;)
    {
        this_thread::sleep_for (KRenderLoopInterval); // Render loop interval

        UI::ShowMatrix (Matrix);
        UI::ShowControls (CurrentPlayer);

        if (!MovementHandler (PlayerPositions, CurrentPlayer, Size, GameMode))
            continue;

        GameMode.BuildMatrix(Matrix, PlayerPositions, (*KTokens.rbegin ()));

        CurrentPlayer++;
        if (CurrentPlayer >= GameMode.PlayerCount)
            CurrentPlayer = 0;
    }

    return 0;
}