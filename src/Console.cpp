#include "Console.h"

using namespace std;

namespace Console
{
    std::ostream& operator<< (std::ostream& os, const Colors& Color)
    {
	    return os << "\033[" << static_cast<unsigned> (Color) << "m";
    }

    std::ostream& operator<< (std::ostream& os, const BackgroundColors& Color)
    {
	    return os << "\033[" << static_cast<unsigned> (Color) << "m";
    }

    void ClearScreen ()
    {
        cout << "\033[H\033[2J";
    }
}