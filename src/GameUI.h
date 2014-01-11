/**
 * @file   GameUI.h
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Colors of each token, UI functions declarations
 *
 **/
#pragma once

#include <utility>
#include <map>

#include "Console.h"
#include "Game.h"

namespace nsGame
{
    namespace nsUI
    {
        using namespace nsConsole;

        /**
         * 
         * @brief Colors of each token.
         * 
         **/
        const std::map<char, std::pair<Colors, BackgroundColors>> KTokenColors =
        {
            { 'X', { Colors::KRed,      BackgroundColors::KDefault  } },
            { 'O', { Colors::KGreen,    BackgroundColors::KDefault  } },
            { '#', { Colors::KMagenta,  BackgroundColors::KDefault  } },
            { '@', { Colors::KYellow,   BackgroundColors::KDefault  } },
            { '|', { Colors::KBlack,    BackgroundColors::KWhite    } },
            { ' ', { Colors::KDefault,  BackgroundColors::KDefault  } } // Colors of empty token are not used as they come from config file.
        };

        /**
         * 
         * @brief Displays the borders and the game matrix, applying the correct colors to the tokens.
         * 
         * 
         **/
        void ShowMatrix (const CMatrix& Matrix);

        /**
         * 
         * @brief Indicates which controls the current player should be using to move.
         * 
         **/
        void ShowControls (const unsigned CurrentPlayer);
    } // UI
} // nsGame