/**
 * @file   Console.h
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Console manipulation (colors, timed-out noncanonical input, VT100)
 *
 **/
#pragma once

#include <iostream>

/**
 * 
 * @namespace nsConsole
 * 
 **/
namespace nsConsole
{
    /**
     * 
     * @brief Color codes for each 
     * 
     **/
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
    }; // Colors

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
    }; // BackgroundColors

    /**
     * 
     * @brief Colors output with VT100 syntax.
     * 
     */
    std::ostream& operator<< (std::ostream& os, const Colors& Color);
    
    /**
     * 
     * @brief Colors output background with VT100 syntax.
     * 
     */
    std::ostream& operator<< (std::ostream& os, const BackgroundColors& Color);

    /**
     * 
     * @brief Clears the screen with VT100 syntax.
     * 
     * @warning Doesn't actually cleans anything, just prints enough blank lines so that previous stuff isn't visible.
     * 
     */
    void ClearScreen ();

    /**
     * 
     * @brief Waits for a key to be pressed (blocking) or until the timeout expires.
     *
     * @return True if key was pressed, false otherwise. 
     * 
     **/
    bool WaitForKeyPress(const unsigned TimeOut);
    
    /**
     * 
     * @brief Gets the count of rows and columns in the terminal.
     * 
     * 
     **/
    void GetScreenSize (unsigned& x, unsigned& y);
    
    /**
     * 
     * @brief Allows getting input without buffering, which means that the user need not press 'Enter' to send input.
     * 
     * @author http://www.cplusplus.com/forum/general/29137/#msg157988
     * 
     **/
    void DisableCanonicalInputMode ();
} // nsConsole