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
            { ' ', { Colors::KDefault,  BackgroundColors::KDefault  } }
        };

        void ShowMatrix (const CMatrix& Matrix);
        void ShowControls (const unsigned CurrentPlayer);
    }
}