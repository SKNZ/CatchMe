/**
 * @author F. Narenji
 *
 * @date   19/12/2013
 *
 * @brief  Main file - Runnable
 *
**/
#include <iostream>

#include "Game.h"

int main (int argc, char** argv)
{
    try
    {
        return Game::Run ();
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "You failed to write proper code. " << e.what () << std::endl;
        return EXIT_FAILURE;
    }
}
