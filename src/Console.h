#pragma once

#include <iostream>

namespace Console
{
    enum struct Colors : unsigned
    {
        KDefault    = 0,
        KBlack      = 30,
        KRed        = 31,
        KGreen      = 32,
        KYellow     = 33,
        KBlue       = 34,
        KMagenta    = 35,
        KCyan       = 36,
        KWhite      = 37
    };
	
    enum struct BackgroundColors : unsigned
    {
        KDefault    = 0,
        KBlack      = 40,
        KRed        = 41,
        KGreen      = 42,
        KYellow     = 43,
        KBlue       = 44,
        KMagenta    = 45,
        KCyan       = 46,
        KWhite      = 47
    };

    // This allows passing Colors directly to cout !
    std::ostream& operator<< (std::ostream& os, const Colors& Color);
    std::ostream& operator<< (std::ostream& os, const BackgroundColors& Color);

    void ClearScreen ();

    /**
     * 
     * @brief Waits for a key to be pressed (blocking) or until the timeout expires.
     *
     * @return True if key was pressed, false otherwise. 
     * 
     **/
    bool WaitForKeyPress(const unsigned TimeOut);
    void GetScreenSize (unsigned& x, unsigned& y);
    
    /**
     * 
     * @brief Allows getting input without buffering, which means that the user need not press 'Enter' to send input.
     * 
     * @author http://www.cplusplus.com/forum/general/29137/#msg157988
     * 
     **/
    void DisableCanonicalInputMode ();
}