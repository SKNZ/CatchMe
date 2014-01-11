#include <sys/ioctl.h>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <poll.h>

#include "Console.h"

using namespace std;

std::ostream& NSConsole::operator<< (std::ostream& os, const Colors& Color)
{
    return os << "\033[" << static_cast<unsigned> (Color) << "m";
}

std::ostream& NSConsole::operator<< (std::ostream& os, const BackgroundColors& Color)
{
    return os << "\033[" << static_cast<unsigned> (Color) << "m";
}

void NSConsole::ClearScreen ()
{
    cout << "\033[H\033[2J";
}

// http://www.cplusplus.com/forum/general/5304/#msg23940
bool NSConsole::WaitForKeyPress (const unsigned TimeOut)
{
    pollfd pls[1];
    
    pls[0].fd     = STDIN_FILENO;
    pls[0].events = POLLIN | POLLPRI;
    
    return poll (pls, 1, TimeOut ) > 0;
}

// http://stackoverflow.com/a/1022961
void NSConsole::GetScreenSize (unsigned& x, unsigned& y)
{
    winsize w;

    ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);

    x = w.ws_col;
    y = w.ws_row;
}

// Restore previous mode
void EnableCanonicalInputMode ()
{
    termios term;

    tcgetattr (STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr (0, TCSANOW, &term);
}

// Manipulating the terminal requires sacrificing C++ :/
void NSConsole::DisableCanonicalInputMode ()
{
    termios term;

    tcgetattr (STDIN_FILENO, &term); // Get terminal attributes
    term.c_lflag &= ~(ICANON | ECHO); // Remove canonical mode, echo
    tcsetattr (STDIN_FILENO, TCSANOW, &term); // Set modified terminal attributes

    cin.sync_with_stdio(); // This is necessary for non-blocking timed I/O using poll.

    atexit (EnableCanonicalInputMode); // Once the program exits, put it back the way it was before
} // DisableCanonicalInputMode

