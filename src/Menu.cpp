#include <vector>
#include <iostream>
#include <thread>

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

/**
 * 
 * @todo Cleans this shit up. Make it readable. Also try to add arrow keys support for menu browsing... 
 * 
 **/
void Menu::Run ()
{
    if (MenuItems.empty ())
        throw "Menu::Run - The menu was empty.";

    unsigned MaxItemNameLength = 0;
    for (pair<string, function<void (void)>> Pair : MenuItems)
        if (Pair.first.size () > MaxItemNameLength)
            MaxItemNameLength = Pair.first.size ();

    unsigned SizeX, SizeY;
    Console::GetScreenSize (SizeX, SizeY);

    unsigned MenuStartPosition = SizeX / 2 - MaxItemNameLength / 2;
    unsigned Selection = 0;
    
    for (;;)
    {
        Console::ClearScreen ();

        for (unsigned i = 0; i < MenuStartPosition; ++i)
            cout << ' ';

        cout << BackgroundColors::KMagenta;

        for (unsigned i = 0; i < MaxItemNameLength + 20; ++i)
            cout << ' ';
        
        cout << BackgroundColors::KDefault << endl;

        
        unsigned Counter = 0;
        for (pair<string, function<void (void)>> Pair : MenuItems)
        {
            for (unsigned i = 0; i < MenuStartPosition; ++i)
                cout << ' ';
            
            cout << BackgroundColors::KMagenta << ' '  << BackgroundColors ::KDefault << "    ";

            if (Counter == Selection)
                cout << BackgroundColors::KWhite << Colors::KBlack << Pair.first;
            else cout << Pair.first;

            cout << BackgroundColors::KDefault;
            
            for (unsigned i = 0; i < MaxItemNameLength + 20 - 6 - Pair.first.size (); ++i)
                cout << ' ';

            cout << BackgroundColors::KMagenta << ' ' << BackgroundColors::KDefault << endl;
            Counter++;
        }

        for (unsigned i = 0; i < MenuStartPosition; ++i)
                cout << ' ';
        
        cout << BackgroundColors::KMagenta << ' '  << BackgroundColors ::KDefault << "    ";
        
        for (unsigned i = 0; i < MaxItemNameLength + 20 - 6; ++i)
            cout << ' ';

        cout << BackgroundColors::KMagenta << ' ' << BackgroundColors::KDefault;
        cout << endl;
        
        for (unsigned i = 0; i < MenuStartPosition; ++i)
            cout << ' ';

        cout << BackgroundColors::KMagenta;

        for (unsigned i = 0; i < MaxItemNameLength + 20; ++i)
            cout << ' ';
        
        cout << BackgroundColors::KDefault << endl;
        
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
                break;
        }
    }
}
