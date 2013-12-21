#include "GameUI.h"

#include <iostream>

using namespace std;

namespace Game
{
    namespace UI
    {
        void ShowMatrix (const CMatrix & Matrix)
        {
            for (unsigned i = 0; i < RenderMatrixSize.second + 2; ++i)
                cout << BackgroundColors::KGreen << ' ';

            cout << BackgroundColors::KDefault << endl;
            
            for (CLine Line : Matrix)
            {
                cout << BackgroundColors::KGreen << ' ' << BackgroundColors::KDefault;

                for (char C : Line)
                {
                    if (KColorsByToken.find(C) != KColorsByToken.cend())
                        cout << KColorsByToken.at(C).first << KColorsByToken.at(C).second; // We use at for const-correctness
                    else
                        cout << Colors::KDefault << BackgroundColors::KDefault;

                    cout << C;
                }

                cout << BackgroundColors::KGreen << ' ' << BackgroundColors::KDefault << endl;
            }

            cout << BackgroundColors::KGreen;

            for (unsigned i = 0; i < RenderMatrixSize.second + 2; ++i)
                cout << ' ';

            cout << BackgroundColors::KDefault << endl;
        }
    }
}