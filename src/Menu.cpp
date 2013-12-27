#include <vector>
#include <iostream>
#include <thread>
#include <string>

#include "Menu.h"
#include "Console.h"

using namespace std;
using namespace Console;

vector<pair<string, function<void (void)>>> MenuItems;

void Menu::AddItem (string ItemName, function<void(void)> Callback)
{
    MenuItems.push_back (make_pair (ItemName, Callback));
}

void Menu::Clear ()
{
    MenuItems.clear ();
}

void DrawBorder (unsigned SizeX)
{
    // The menu begins at 1/4 of the screen.
    for (unsigned i = 0; i < SizeX / 4; ++i)
        cout << ' ';

    cout << BackgroundColors::KMagenta;

    // It takes 2/4 of the screen.
    for (unsigned i = 0; i < SizeX / 2; ++i)
        cout << ' ';
    
    cout << BackgroundColors::KDefault << endl;
}

void DrawItem (int SizeX, std::string Text, bool Selected)
{
    for (unsigned i = 0; i < SizeX / 4; ++i)
        cout << ' ';
    
    // Left border
    cout << BackgroundColors::KMagenta << ' '  << BackgroundColors ::KDefault;

    if (Selected)
        cout << BackgroundColors::KWhite << Colors::KBlack;
    
    cout << Text << BackgroundColors::KDefault;
    
    // Right padding
    for (unsigned i = 0; i < (SizeX / 2) - Text.size () - 2; ++i)
        cout << ' ';

    // Right border
    cout << BackgroundColors::KMagenta << ' ' << BackgroundColors::KDefault << endl;
}

/**
 * 
 * @todo Cleans this shit up. Make it readable. Also try to add arrow keys support for menu browsing... 
 * 
 **/
void Menu::Run ()
{
    if (MenuItems.empty ())
        throw "Menu::Run - The menu was empty.";

    unsigned SizeX, SizeY;
    Console::GetScreenSize (SizeX, SizeY);

    unsigned Selection = 0;
    
    for (;;)
    {
        Console::ClearScreen ();

        // Top border
        DrawBorder(SizeX);
       
        unsigned Counter = 0;
        for (pair<string, function<void (void)>> Pair : MenuItems)
        {
            DrawItem(SizeX, Pair.first, Counter == Selection);            
            Counter++;
        }

        // Empty line
        DrawItem(SizeX, " ", false);
        
        // Bottom border
        DrawBorder(SizeX);
        
        switch (cin.get ())
        {
            case 'z': // Up
                Selection = Selection == 0 ? MenuItems.size() - 1 : Selection - 1; // If first item, then go to last item, else move previous item
                break;
            case 's': // Down
                Selection = Selection == MenuItems.size() - 1 ? 0 : Selection + 1; // If last item, then go to first item, else move next item
                break;
            case '\n': // Validation
                Console::ClearScreen ();
                (MenuItems.begin () + Selection)->second (); // Call the Callback function
                return;
                break;
            default:
                cout << "Use Z to go up, S to go down and Enter to validate." << endl;
                this_thread::sleep_for(KErrorMessageDisplayTime);
                Console::ClearInputBuffer ();
                break;
        }
    }
}
