#include "Console.h"

using namespace std;

std::ostream& Console::operator<< (std::ostream& os, const Colors& Color)
{
    return os << "\033[" << static_cast<unsigned> (Color) << "m";
}

std::ostream& Console::operator<< (std::ostream& os, const BackgroundColors& Color)
{
    return os << "\033[" << static_cast<unsigned> (Color) << "m";
}

void Console::ClearScreen ()
{
    cout << "\033[H\033[2J";
}

void Console::ClearInputBuffer ()
{
    static string Trash;
    getline(cin, Trash);
}

