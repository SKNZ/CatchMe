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
    enum struct Colors : unsigned
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
	
	enum struct BackgroundColors : unsigned
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
	std::ostream& operator<< (std::ostream& os, const Colors& Color)
	{
		return os << "\033[" << static_cast<unsigned> (Color) << "m";
	}
	
	std::ostream& operator<< (std::ostream& os, const BackgroundColors& Color)
	{
		return os << "\033[" << static_cast<unsigned> (Color) << "m";
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
            cout << Colors::KDefault;

            for (unsigned i = 0; i < SizeX + 2; ++i)
                cout << Colors::KGreen << ' ';
            
            cout << endl;

            for (CLine Line : Matrix)
            {
                cout << Colors::KGreen << ' ' << Colors::KDefault;

                for (char C : Line)
                    cout << C;

                cout << Colors::KGreen << ' ' << endl;
            }

            for (unsigned i = 0; i < SizeX + 2; ++i)
                cout << ' ';

            cout << endl;
            cout << Colors::KDefault;
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
