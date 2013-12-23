#include "GameUI.h"

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * 
 * @brief Displays the borders and the game matrix, applying the correct colors to the tokens.
 * 
 * @todo Constants for border color should be replaced by a (const) variable.
 * 
 */
void Game::UI::ShowMatrix (const CMatrix & Matrix)
{
    Console::ClearScreen ();

    // Upper border
    for (unsigned i = 0; i < Matrix.begin ()->size () + 2; ++i)
        cout << BackgroundColors::KGreen << ' ';

    cout << BackgroundColors::KDefault << endl;
    
    for (CLine Line : Matrix)
    {
        // Left border
        cout << BackgroundColors::KGreen << ' ' << BackgroundColors::KDefault;

        for (char C : Line)
        {
            try
            {
                cout << KTokenColors.at(C).second << KTokenColors.at(C).first; // We use at() for const-correctness
            }
            catch (out_of_range e)
            {
                cerr << "Color information for token '" << C << "' is missing. Assuming default colorset." << endl;
                cout << Colors::KDefault << BackgroundColors::KDefault;
            }

            cout << C;
        }

        // Right border
        cout << BackgroundColors::KGreen << ' ' << BackgroundColors::KDefault << endl;
    }

    // Bottom border
    cout << BackgroundColors::KGreen;
    for (unsigned i = 0; i < Matrix.begin ()->size () + 2; ++i)
        cout << ' ';

    cout << BackgroundColors::KDefault << endl;
}

/**
 * 
 * @brief Indicates which controls the current player should be using to move.
 * 
 */
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
