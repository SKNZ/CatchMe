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
        const std::map<char, std::pair<Colors, BackgroundColors>> KColorsByToken =
        {
            { 'X', { Colors::KRed,      BackgroundColors::KWhite    } },
            { 'O', { Colors::KGreen,    BackgroundColors::KWhite    } },
            { ' ', { Colors::KDefault,  BackgroundColors::KDefault  } }
        };

        const char KEmpty = ' ';

        void ShowMatrix (const CMatrix & Matrix);
    }
}