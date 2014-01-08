#pragma once

#include <string>
#include <chrono>

namespace Game
{
    namespace Config
    {
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
    }
}