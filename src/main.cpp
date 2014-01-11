/**
 * @file   main.cpp
 * 
 * @author F. Narenji, O. Richit, H. Morales, V. Pelegrin
 *
 * @date   12/01/2014
 *
 * @brief  Main file.
 *
 **/
#include <iostream>

#include "Game.h"

int main (int argc, char** argv)
{
    try
    {
        return nsGame::Run ();
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "You failed to write proper code. " << e.what () << std::endl;
        return EXIT_FAILURE;
    }
}
