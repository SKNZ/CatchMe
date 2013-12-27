#include <sys/ioctl.h>
#include <cstdio>
#include <termios.h>
#include <unistd.h>

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


void Console::GetScreenSize (unsigned& x, unsigned& y)
{
    winsize w;

    ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);

    x = w.ws_row;
    y = w.ws_col;
}

// Restore previous mode
void EnableCanonicalInputMode ()
{
    termios term;

    tcgetattr (STDIN_FILENO, &term); 
    term.c_lflag |= ICANON | ECHO;
    tcsetattr (0, TCSANOW, &term);
}

void Console::DisableCanonicalInputMode ()
{
    termios term;

    tcgetattr (STDIN_FILENO, &term); // Get terminal attributes
    term.c_lflag &= ~(ICANON | ECHO); // Remove canonical mode, echo
    tcsetattr (STDIN_FILENO, TCSANOW, &term); // Set modified terminal attributes

    atexit (EnableCanonicalInputMode); // Once the program exits, put it back the way it was before
}

