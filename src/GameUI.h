#pragma once

#include <utility>
#include <map>

#include "Console.h"
#include "Game.h"

namespace Game
{
    namespace UI
    {
        using namespace Console;

        // Constants        
        const std::map<char, std::pair<Colors, BackgroundColors>> KTokenColors =
        {
            { 'X', { Colors::KRed,      BackgroundColors::KDefault  } },
            { 'O', { Colors::KGreen,    BackgroundColors::KDefault  } },
            { '#', { Colors::KMagenta,  BackgroundColors::KDefault  } },
            { '@', { Colors::KYellow,   BackgroundColors::KDefault  } },
            { '|', { Colors::KCyan,     BackgroundColors::KRed      } },
            { ' ', { Colors::KDefault,  BackgroundColors::KDefault  } } // We want alternate colors there, the easiest way to achieve this is to hardcode it
        };

        /**
         * 
         * @brief Displays the borders and the game matrix, applying the correct colors to the tokens.
         * 
         * @todo Constants for border color should be replaced by a (const) variable.
         * 
         **/
        void ShowMatrix (const CMatrix& Matrix);

        /**
         * 
         * @brief Indicates which controls the current player should be using to move.
         * 
         **/
        void ShowControls (const unsigned CurrentPlayer);
    }
}