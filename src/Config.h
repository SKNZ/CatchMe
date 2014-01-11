#pragma once

#include "Console.h"

#include <string>
#include <chrono>

using namespace Console;

namespace NSGame
{
    namespace Config
    {
        /**
         * 
         * @brief The name of the config file.
         * 
         **/
        const std::string KFileName = "conf.xml";
        
        /**
         *  
         * @brief Parse the configuration file.
         * 
         **/
        void LoadFile ();

        /**
         * 
         * @brief The duration during which the game will be suspended to let the player read the error message.
         * 
         * @warning This should only be used for gameplay related error messages, such as wrong key
         *          and not for technical problems (such as exceptions reports).
         * 
         **/
         extern unsigned ErrorMessageDisplayTime;
        
        /**
         * 
         * @brief The interval between each render loop.
         * 
         **/
         extern unsigned RenderLoopInterval;
         
         /**
          * 
          * @brief How long should we wait for a player to give us something before we fuck him up ?
          * 
          **/
         extern unsigned TurnTimeoutDelay;
         
         /**
          * 
          * @brief How long the bot should wait before making his move (its aimed at making it look more real). 
          * 
          **/
         extern unsigned BotPlayDelay;
         
         /**
          * 
          * @brief The color of the the game matrix border
          * 
          **/
         extern BackgroundColors BorderColor;
         
        /**
          * 
          * @brief The color of the the game matrix case (even)
          * 
          **/
         extern BackgroundColors CaseColor1;
         
         /**
          * 
          * @brief The color of the the game matrix case (uneven)
          * 
          **/
         extern BackgroundColors CaseColor2;
         
         /**
          * 
          * @brief The color of the the menu border
          * 
          **/
         extern BackgroundColors MenuBorderColor;
    }
}