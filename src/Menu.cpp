/**
 * @file   Menu.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Add item to menu, clear menu, draw menu helpers, run menu definitions
 *
 **/
#include <vector>
#include <iostream>
#include <thread>
#include <string>
#include <sstream>

#include "Menu.h"
#include "Console.h"
#include "Config.h"

using namespace std;
using namespace NSConsole;
using namespace NSGame;

/**
 * 
 * @brief Items contained in the menu associated with their callbacks.
 * 
 **/
vector<pair<string, function<void (void)>>> MenuItems;

void NSMenu::AddItem (string ItemName, function<void(void)> Callback)
{
    MenuItems.push_back (make_pair (ItemName, Callback));
}

void NSMenu::Clear ()
{
    MenuItems.clear ();
}

namespace
{
    /**
    * 
    * @brief Draws a horizontal border.
    * 
    * @param SizeX The size of the console (or render target) in terms of characters on the X axis.
    * 
    **/
    void DrawBorder (unsigned SizeX)
    {
        unsigned Quarter = SizeX / 4;
        // The menu begins at 1/4 of the screen.
        for (unsigned i = 0; i < Quarter; ++i)
            cout << ' ';

        cout << NSConfig::MenuBorderColor;

        // It takes 2/4 of the screen.
        for (unsigned i = 0; i < Quarter * 2; ++i)
            cout << ' ';

        cout << BackgroundColors ::KDefault << endl;
    } // DrawBorder

    /**
    * 
    * @brief Center and display item.
    * 
    * @param SizeX The size of the console (or render target) in terms of characters on the X axis.
    * @param Selected Whether the item is highlighted.
    * 
    **/
    void DrawItem (int SizeX, std::string Text, bool Selected)
    {
        unsigned Quarter = SizeX / 4;
        for (unsigned i = 0; i < Quarter; ++i)
            cout << ' ';
        
        // Left border
        cout << NSConfig::MenuBorderColor << ' ' << BackgroundColors ::KDefault;

        // Left padding
        // Minus one for the border
        for (unsigned i = 0; i < (Quarter * 2 - Text.size ()) / 2 - 1; ++i)
            cout << ' ';

        if (Selected)
            cout << BackgroundColors::KWhite << Colors::KBlack;

        cout << Text << BackgroundColors::KDefault;

        // Right padding
        // Minus one for the border, minus one if the text size is uneven
        for (unsigned i = 0; i < (Quarter * 2 - Text.size ()) / 2 - (Text.size () % 2 ? 0 : 1); ++i)
            cout << ' ';

        // Right border
        cout << NSConfig::MenuBorderColor << ' ' << BackgroundColors::KDefault << endl;
    } // DrawItem
} // namespace

void NSMenu::Run (bool IsWinMenu)
{
    if (MenuItems.empty ())
        throw "Menu::Run - The menu was empty.";

    unsigned Selection = 0;

    for (;;)
    {
        unsigned SizeX = 0, SizeY = 0;
        NSConsole::GetScreenSize (SizeX, SizeY);

        NSConsole::ClearScreen ();

        // Top border
        DrawBorder (SizeX);

        // Empty line
        DrawItem (SizeX, " ", false);

        // SUCH LOGO !
        if (IsWinMenu)
        {
            // From http://ascii.co.uk/art/palmtree
            DrawItem(SizeX, "        __ _.--..--._ _", false);
            DrawItem(SizeX, "     .-' _/   _/\\_   \\_'-.", false);
            DrawItem(SizeX, "    |__ /   _/\\__/\\_   \\__|", false);
            DrawItem(SizeX, "       |___/\\_\\__/  \\___|", false);
            DrawItem(SizeX, "              \\__/", false);
            DrawItem(SizeX, "              \\__/", false);
            DrawItem(SizeX, "               \\__/", false);
            DrawItem(SizeX, "                \\__/", false);
            DrawItem(SizeX, "             ____\\__/___", false);
            DrawItem(SizeX, "       . - '             ' -.", false);
            DrawItem(SizeX, "      /                      \\", false);
            DrawItem(SizeX, "~~~~~~~  ~~~~~ ~~~~~  ~~~ ~~~  ~~~~~", false);
            DrawItem(SizeX, "  ~~~   ~~~~~   ~!~~   ~~ ~  ~ ~ ~pjb", false);
        }
        else
        {
            DrawItem (SizeX, "  _____      _       _     __  __      ", false);
            DrawItem (SizeX, " / ____|    | |     | |   |  \\/  |     ", false);
            DrawItem (SizeX, "| |     __ _| |_ ___| |__ | \\  / | ___ ", false);
            DrawItem (SizeX, "| |    / _` | __/ __| '_ \\| |\\/| |/ _ \\", false);
            DrawItem (SizeX, "| |___| (_| | || (__| | | | |  | |  __/", false);
            DrawItem (SizeX, " \\_____\\__,_|\\__\\___|_| |_|_|  |_|\\___|", false);
        }

        DrawItem (SizeX, " ", false);
        DrawItem (SizeX, " ", false);

        unsigned Counter = 0;
        for (pair<string, function<void (void)>> Pair : MenuItems)
        {
            DrawItem (SizeX, Pair.first, Counter == Selection);
            Counter++;
        }

        DrawItem (SizeX, " ", false);
        
        // Bottom border
        DrawBorder (SizeX);

        // Handle user input
        switch (tolower (cin.get ()))
        {
            case 'z': // Up
                Selection = Selection == 0 ? MenuItems.size() - 1 : Selection - 1; // If first item, then go to last item, else move previous item
                break;
            case 's': // Down
                Selection = Selection == MenuItems.size() - 1 ? 0 : Selection + 1; // If last item, then go to first item, else move next item
                break;
            case '\n': // Validation
                NSConsole::ClearScreen ();
                MenuItems[Selection].second (); // Call the Callback function
                return;
                break;
            default:
                cout << "Use Z to go up, S to go down and Enter to validate." << endl;
                NSConsole::WaitForKeyPress (NSConfig::ErrorMessageDisplayTime);
                break;
        } // switch
    } // for
} // Run

void NSMenu::ShowSimpleWinScreen (const vector<bool>& PlayerLifeStates, std::vector<char> Tokens, vector<unsigned> TurnCounters)
{
    Clear ();

    for (unsigned i = 0; i < PlayerLifeStates.size (); ++i)
        if (PlayerLifeStates [i])
        {
            stringstream Winner;
            Winner << "Player " << i + 1 << " '" << Tokens [i] << "' won in " << TurnCounters [i] << " turn.";
            AddItem (Winner.str());
        }

    Run (true);
}
