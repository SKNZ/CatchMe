#include <iostream>
#include <iomanip>
#include "GameUI.h"
#include "Menu.h"

using namespace std;

void Game::UI::ShowMatrix (const CMatrix & Matrix)
{
    Console::ClearScreen ();
    
    unsigned EmptyCasesCounter = 0;
    unsigned TotalWidth = Matrix.begin ()->size () * 3 + 2;

    cout << endl << ' ';
    
    // Upper border
    for (unsigned i = 0; i < TotalWidth; ++i)
        cout << BackgroundColors::KGreen << ' ';

    cout << BackgroundColors::KDefault << endl;
    
    for (CLine Line : Matrix)
    {
        // Left border
        cout << ' ' << BackgroundColors::KGreen << ' ' << BackgroundColors::KDefault;

        for (char C : Line)
        {
            try
            {
                cout << KTokenColors.at(C).first;

                if (KTokenColors.at(C).second == BackgroundColors::KDefault)
                {
                    if (EmptyCasesCounter % 2 == 0)
                        cout << BackgroundColors::KBlue;
                    else
                        cout << BackgroundColors::KBlack;
                }
                else
                {
                    cout << KTokenColors.at(C).second; // We use at() for const-correctness
                }
            }
            catch (out_of_range e)
            {
                cerr << "Color information for token '" << C << "' is missing. Assuming default colorset." << endl;
                cout << Colors::KDefault << BackgroundColors::KDefault;
            }

            cout << ' ' << C << ' ';
            EmptyCasesCounter++;
        }

        // Right border
        cout << BackgroundColors::KGreen << ' ' << BackgroundColors::KDefault << endl;

        ++EmptyCasesCounter;
    }

    // Bottom border
    cout << ' ' << BackgroundColors::KGreen;
    for (unsigned i = 0; i < TotalWidth; ++i)
        cout << ' ';

    cout << BackgroundColors::KDefault << endl;
}

void Game::UI::ShowControls (const unsigned int CurrentPlayer)
{
    cout << endl << "Current player: " << KTokens.at (CurrentPlayer) << endl
        << "Controls: " << endl
        << setw(16) <<  "UpLeft(" << KControlsByToken.at (KTokens.at (CurrentPlayer)) [0] << ") "
        << setw(16) <<  "Up(" << KControlsByToken.at (KTokens.at (CurrentPlayer)) [1] << ") "
        << setw(16) <<  "UpRight(" << KControlsByToken.at (KTokens.at (CurrentPlayer)) [2] << ") " << endl
        << setw(16) <<  "Left(" << KControlsByToken.at (KTokens.at (CurrentPlayer)) [3] << ") "
        //<< setw(16) <<  "Stay(" << KControlsByToken.at (KTokens.at (CurrentPlayer))[4] << ") "
        << setw(35) <<  "Right(" << KControlsByToken.at (KTokens.at (CurrentPlayer)) [5] << ") " << endl
        << setw(16) <<  "DownLeft(" << KControlsByToken.at (KTokens.at (CurrentPlayer)) [6] << ") "
        << setw(16) <<  "Down(" << KControlsByToken.at (KTokens.at (CurrentPlayer)) [7] << ") "
        << setw(16) <<  "DownRight(" << KControlsByToken.at (KTokens.at (CurrentPlayer)) [8] << ") " << endl;
}

