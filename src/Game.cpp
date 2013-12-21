#include "Game.h"
#include "GameUI.h"

#include <iostream>
#include <limits>

using namespace std;

namespace Game
{
    void GetPlayerCount (unsigned& PlayerCount)
    {
        do
        {
            cout << "How many players do want you to play with (2-4) ? " << flush;

            char c = cin.get ();
            cin.ignore (numeric_limits<streamsize>::max (), '\n'); // Get a single char, drop the rest of the input buffer until the first end line.

            if (!isdigit (c))
            {
                cerr << "You must enter a digit." << endl;
                continue;
            }

            PlayerCount = c - '0'; // Digits in the ASCII table are sorted in ascending order.

            if (PlayerCount < 2 || PlayerCount > 4)
            {
                cerr << "The player count must be between 1 and 4." << endl;
                PlayerCount = 0;
            }

            cout << "There will be " << PlayerCount << " players." << endl;

        } while (0 == PlayerCount);
    }

    void InitializeRenderMatrix (CMatrix & RenderMatrix, const CPosition & Size, const char EmptyToken)
    {
        RenderMatrix.resize(Size.first);
        
        for (CLine & Line : RenderMatrix)
            Line.resize (Size.second, EmptyToken);
    }
    
    void InitializePlayerPositions (CPositions & PlayerPositions, const unsigned PlayerCount, const CPosition & Size)
    {
        PlayerPositions.resize(PlayerCount);
        for (unsigned i = 0; i < PlayerCount; ++i)
        {
            switch (i)
            {
                case 0:
                    PlayerPositions[0] = { 0, Size.second }; // Top right
                    break;
                case 1:
                    PlayerPositions[1] = { Size.first, 0 }; // Bottom left
                    break;
                case 2:
                    PlayerPositions[2] = { 0, 0 }; // Top left
                    break;
                case 3:
                    PlayerPositions[3] = { Size.first, Size.second }; // Bottom right
                    break;
            }
        }
    }

    int Run ()
    {
        unsigned            PlayerCount = 0;
        CMatrix             RenderMatrix;
        vector<CPosition>   PlayerPositions;
        
        GetPlayerCount (PlayerCount);
        InitializePlayerPositions (PlayerPositions, PlayerCount, RenderMatrixSize);
        InitializeRenderMatrix (RenderMatrix, RenderMatrixSize, UI::KEmpty);

        UI::ShowMatrix (RenderMatrix);

        return 0;
    }
}