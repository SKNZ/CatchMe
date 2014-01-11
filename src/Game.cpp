/**
 * @file   Game.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Main game file, contains game loop, user interaction
 *
 **/
#include <iostream>
#include <sstream>
#include <thread>
#include <set>
#include <cstdlib>

#include "Menu.h"
#include "Game.h"
#include "GameUI.h"
#include "Config.h"
#include "Console.h"
#include "GameMode.h"
#include "Bot.h"

using namespace std;

namespace
{
    using namespace nsGame;

    /**
     *
     * @brief Two step game mode selection screen.
     *          It finds all the different game mode type by taking the first part (before space)
     *          of every game mode name. It ask which you want and then gives you all the game modes
     *          where the name begins with the game mode type you selected.
     *
     **/
    void SelectGameMode (SGameMode& GameMode)
    {
        nsMenu::Clear ();

        set<string> GameModeTypes;

        for (SGameMode CurrentGameMode : KGameModes)
        {
            stringstream Text (CurrentGameMode.Name);
            std::string GameModeType;
            if (getline (Text, GameModeType, ' '))
                GameModeTypes.insert (GameModeType);
        }

        std::string SelectedGameModeType;

        for (string GameModeType : GameModeTypes)
            nsMenu::AddItem (GameModeType, [&SelectedGameModeType, GameModeType] () { SelectedGameModeType = GameModeType; });
        
        nsMenu::AddItem("Quitter", [] () { exit(0); });

        nsMenu::Run ();

        nsMenu::Clear ();

        for (SGameMode CurrentGameMode : KGameModes)
            if (CurrentGameMode.Name.find (SelectedGameModeType) != string::npos)
                nsMenu::AddItem (CurrentGameMode.Name, [&GameMode, CurrentGameMode] () { GameMode = CurrentGameMode; });

        nsMenu::Run ();
    } // SelectGameMode

    /**
     * 
     * @brief Gets the user input and if it is a valid control for the current player.
     *          If the user doesn't give any input in a certain time (Config)
     *          a bot action is executed.
     *
     **/
    bool GetUserAction (size_t& Action, unsigned CurrentPlayer, bool AllowStay, const CMatrix& Matrix, const std::vector<bool>& PlayerLifeStates, CPositions& PlayerPositions)
    {
        if (nsConsole::WaitForKeyPress (nsConfig::TurnTimeoutDelay))
        {
            char Opcode = tolower (cin.get ());

            Action = KControlsByToken.at (CurrentPlayer).find (Opcode);
            if (Action == string::npos || (!AllowStay && Action == 4)) // 4 is the position of the stay (middle) key (such as S or 5).
            {
                cout << "The key you entered wasn't valid." << endl;
                nsConsole::WaitForKeyPress (nsConfig::ErrorMessageDisplayTime); // Wait a defined amount of time for the message to be shown.

                return false;
            }
        }
        else
        {
            nsBot::MakeMove (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer);
        }

        return true;
    } // GetUserAction

    /**
     *
     * @brief Asks the user whether he wants a certain player to be played by a bot. 
     *
     **/
    void AddBots (const SGameMode& GameMode, vector<bool>& IsPlayerBot)
    {
        IsPlayerBot.resize (GameMode.PlayerCount, false);
        if (GameMode.PlayerCount < 2) // We only want bots for 1v1 games.

        for (unsigned i = 1; i < IsPlayerBot.size (); ++i)
        {
            nsMenu::Clear ();

            nsMenu::AddItem ("The player " + to_string (i + 1) + " is a bot.",     [&IsPlayerBot, i] () { IsPlayerBot [i] = true; });
            nsMenu::AddItem ("The player " + to_string (i + 1) + " is not a bot.", [&IsPlayerBot, i] () { IsPlayerBot [i] = false; });

            nsMenu::Run ();
        }
    } // AddBots

    /**
     *
     * @brief Converts an action into a grid axis movement and makes the move.
     * 
     **/
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
    } // MovementHandler

    /**
     * 
     * @brief Round logic code (player positions, current player, game over etc)
     * 
     **/
    void DoRound (const SGameMode& GameMode, const CPosition& Size, vector<bool>& PlayerLifeStates, vector<bool>& IsPlayerBot, vector<unsigned>& TurnCounters)
    {
        CPositions      PlayerPositions;
        unsigned        CurrentPlayer = 0; // Whose turn it is
        CMatrix         Matrix;

        PlayerLifeStates.resize (GameMode.PlayerCount, true);
        fill (PlayerLifeStates.begin (), PlayerLifeStates.end (), true);

        TurnCounters.resize (GameMode.PlayerCount, 0);
        fill (TurnCounters.begin (), TurnCounters.end (), 0);

        Matrix.resize (Size.first);

        for (CLine& Line : Matrix)
            Line.resize (Size.second);

        GameMode.InitializeRound (PlayerPositions, GameMode.PlayerCount, Size);

        GameMode.BuildMatrix (Matrix, PlayerPositions, PlayerLifeStates, KTokens [KTokenEmpty]);

        for (;;)
        {
            this_thread::sleep_for (std::chrono::milliseconds (nsConfig::RenderLoopInterval)); // Render loop interval

            nsUI::ShowMatrix (Matrix);
            nsUI::ShowControls (CurrentPlayer);

            if (GameMode.IsGameOver (PlayerLifeStates))
                break;

            if (PlayerLifeStates [CurrentPlayer])
            {
                size_t Action = 0;

                if (IsPlayerBot [CurrentPlayer])
                {
                    nsBot::MakeMove (Matrix, PlayerLifeStates, PlayerPositions, CurrentPlayer);
                    this_thread::sleep_for (std::chrono::milliseconds (nsConfig::BotPlayDelay));
                }
                else
                {
                    if (!GetUserAction (Action, CurrentPlayer, GameMode.AllowStay, Matrix, PlayerLifeStates, PlayerPositions))
                        continue; // Retry !

                    MovementHandler (Action, Matrix, PlayerPositions, CurrentPlayer, Size, GameMode);
                }

                GameMode.ValidatePlayerPositions (Matrix, PlayerPositions, CurrentPlayer, PlayerLifeStates);

                GameMode.BuildMatrix (Matrix, PlayerPositions, PlayerLifeStates, KTokens [KTokenEmpty]);
            } // if (PlayerLifeStates [CurrPlr])

            ++TurnCounters [CurrentPlayer];
            ++CurrentPlayer;
            if (CurrentPlayer >= GameMode.PlayerCount) // Go back to first player if last player reached
                CurrentPlayer = 0;
        } // for (;;)
    } // DoRound
} // namespace

int nsGame::Run ()
{
    nsConsole::DisableCanonicalInputMode ();
    nsConfig::LoadFile ();

    for (;;)
    {
        SGameMode        GameMode;
        CPosition        Size;
        vector<bool>     PlayerLifeStates; // Is dead (false), alive (true)
        vector<bool>     IsPlayerBot;
        vector<unsigned> TurnCounters;

        SelectGameMode (GameMode);
        GameMode.GetSize (Size);

        AddBots (GameMode, IsPlayerBot);

        for (unsigned i = 0; i < GameMode.RoundCount; ++i)
        {
            DoRound (GameMode, Size, PlayerLifeStates, IsPlayerBot, TurnCounters);

            if (i != GameMode.RoundCount) // Don't show if its the last round
            {
                nsMenu::Clear ();

                nsMenu::AddItem ("Next round !");

                nsMenu::Run ();
            }
        }

        GameMode.ShowWinScreen (PlayerLifeStates, KTokens, TurnCounters);
    }

    return 0;
} // Run
