/**
 * @file   GameUI.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Matrix rendering function, current controls display function
 *
 **/
#include <iostream>
#include <iomanip>
#include "GameUI.h"
#include "Menu.h"
#include "Config.h"

using namespace std;

void nsGame::nsUI::ShowMatrix (const CMatrix & Matrix)
{
    const BackgroundColors KBorderColor = nsConfig::BorderColor;
    const BackgroundColors KCaseColor1 = nsConfig::CaseColor1;
    const BackgroundColors KCaseColor2 = nsConfig::CaseColor2;
    
    nsConsole::ClearScreen ();
    
    unsigned EmptyCasesCounter = 0;
    unsigned TotalWidth = Matrix.begin ()->size () * 3 + 2;

    cout << endl << ' ';
    
    // Upper border
    for (unsigned i = 0; i < TotalWidth; ++i)
        cout << KBorderColor << ' ';

    cout << BackgroundColors::KDefault << endl;
    
    for (CLine Line : Matrix)
    {
        // Left border
        cout << ' ' << KBorderColor << ' ' << BackgroundColors::KDefault;

        for (char C : Line)
        {
            try
            {
                cout << KTokenColors.at(C).first;

                if (KTokenColors.at(C).second == BackgroundColors::KDefault)
                {
                    if (EmptyCasesCounter % 2 == 0)
                        cout << KCaseColor1;
                    else
                        cout << KCaseColor2;
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
        cout << KBorderColor << ' ' << BackgroundColors::KDefault << endl;

        ++EmptyCasesCounter;
    }

    // Bottom border
    cout << ' ' << BackgroundColors::KGreen;
    for (unsigned i = 0; i < TotalWidth; ++i)
        cout << ' ';

    cout << BackgroundColors::KDefault << endl;
}

void nsGame::nsUI::ShowControls (const unsigned int CurrentPlayer)
{
    cout << endl << "Current player: " << KTokens.at (CurrentPlayer) << endl
        << "Controls: " << endl
        << setw(16) <<  "UpLeft(" << KControlsByToken.at (CurrentPlayer) [0] << ") "
        << setw(16) <<  "Up(" << KControlsByToken.at (CurrentPlayer) [1] << ") "
        << setw(16) <<  "UpRight(" << KControlsByToken.at (CurrentPlayer) [2] << ") " << endl
        << setw(16) <<  "Left(" << KControlsByToken.at (CurrentPlayer) [3] << ") "
        //<< setw(16) <<  "Stay(" << KControlsByToken.at (CurrentPlayer)[4] << ") "
        << setw(35) <<  "Right(" << KControlsByToken.at (CurrentPlayer) [5] << ") " << endl
        << setw(16) <<  "DownLeft(" << KControlsByToken.at (CurrentPlayer) [6] << ") "
        << setw(16) <<  "Down(" << KControlsByToken.at (CurrentPlayer) [7] << ") "
        << setw(16) <<  "DownRight(" << KControlsByToken.at (CurrentPlayer) [8] << ") " << endl;
}

