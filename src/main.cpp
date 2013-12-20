/**
 * @author F. Narenji
 *
 * @date   19/12/2013
 *
 * @brief  Main file - Runnable
 *
**/
#include <iostream>
#include <vector>
#include <iomanip>
#include <exception>

using namespace std;

namespace Console
{
    enum Colors : unsigned
    {
        KDefault    = 0,
        KBlack      = 30,
        KRed        = 31,
        KGreen      = 32,
        KYellow     = 33,
        KBlue       = 34,
        KMagenta    = 35,
        KCyan       = 36,
        KLightGray  = 37
    };
	
	enum BackgroundColors : unsigned
    {
        KDefault    = 0,
        KBlack      = 40,
        KRed        = 41,
        KGreen      = 42,
        KYellow     = 43,
        KBlue       = 44,
        KMagenta    = 45,
        KCyan       = 46,
        KLightGray  = 47
    };
	
	// This allows passing Colors directly to cout !
	operator<< (std::ostream& os, const Colors& Color) {
		return os << "\033[" << unsigned (Color) << "m";
	}
	
	operator<< (std::ostream& os, const BackgroundColors& Color) {
		return os << "\033[" << unsigned (Color) << "m";
	}

    void ClearScreen ()
    {
        cout << "\033[H\033[2J";
    }
}

namespace Game
{
    typedef vector<char>    CLine;
    typedef vector<CLine>   CMatrix;
    typedef pair<int, int>  CPosition;

    // Constants
    const int SizeX = 10;
    const int SizeY = 10;


    namespace UI
    {
        using namespace Console;

        // Constants
        const vector<char>   KPlayerTokens = { 'X', 'O' };
        const vector<Colors> KPlayerColors = { Colors::KRed, Colors::KGreen };
        const char           KEmpty          = ' ';

        void ShowMatrix(const CMatrix & Matrix)
        {
            ClearScreen();
            cout << Color::KDefault;

            for (unsigned i = 0; i < SizeX + 2; ++i)
                cout << Color::KGreen << ' ';
            
            cout << endl;

            for (CLine Line : Matrix)
            {
                cout << Color::KGreen << ' ' << Color::KDefault;

                for (char C : Line)
                    cout << C;

                cout << Color::KGreen << ' ' << endl;
            }

            for (unsigned i = 0; i < SizeX + 2; ++i)
                cout << ' ';

            cout << endl;
            cout << Color::KDefault;
        }

    }

    int Run()
    {
        CMatrix Matrix(SizeX);

        for (auto & Line : Matrix)
            Line.resize(SizeY, UI::KEmpty);

        UI::ShowMatrix(Matrix);

        return 1;
    }
}

int main(/*int argc, char** argv*/)
{
    return Game::Run();
}
