/**
*
* \file null.cxx
*
* \author Hugo Morales 
*
* \date 19/12/2013
*
* \brief bah le projet quoi
*
**/

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <locale>

using namespace std;

typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille
typedef pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille

namespace 
{
	const char KTokenPlayer1 = 'X';
	const char KTokenPlayer2 = 'O';
	const char KEmpty        = ' ';
	
	void ClearScreen ()
	{
		cout << "\033[H\033[2J";
	}//ClearScreen();
	
	const string KReset   ("0");
	const string KNoir    ("30");
	const string KRouge   ("31");
	const string KVert    ("32");
	const string KJaune   ("33");
	const string KBleu    ("34");
	const string KMAgenta ("35");
	const string KCyan    ("36");
	const string KGris    ("37");
		
	void Couleur (const string & coul)
	{
		cout << "\033[" << coul <<"m";
	}//Couleur();
	
	void  ShowMatrix (const CMatrix & Mat)
	{
		//ClearScreen();
		//Couleur(KReset);
		cout<<endl;
		for(unsigned i=0; i<Mat.size(); ++i)
		{
			for(unsigned j=0; j<Mat.size(); ++j)
			{
				if (Mat[i][j]==KTokenPlayer1)
				{
					//Couleur(KColor1);
					cout<<KTokenPlayer1;
				}
				else if (Mat[i][j]==KTokenPlayer2)
				{
					//Couleur(KColor2);
					cout<<KTokenPlayer2;
				}
				else
					cout<<KEmpty;
			}
		cout<<endl;
		}
	}//ShowMatrix();
	
	void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2)
	{
		for(unsigned i=0; i<NbLine; ++i)
		{
			for(unsigned j=0; j<NbColumn; ++j)
				Mat[i][j]=KEmpty;
		}
		Mat[PosPlayer1.first][PosPlayer1.second]=KTokenPlayer1;
		Mat[PosPlayer2.first][PosPlayer2.second]=KTokenPlayer2;
	}//InitMat();
	
	void MoveToken (CMatrix & Mat, char Move, CPosition  & Pos)
	{
		int Line;
		int Column;
		switch (Move)
		{
			case 'A':
			{
				Line=-1;
				Column=-1;
				break;
			}
			case 'Z':
			{
				Line=0;
				Column=-1;
				break;
			}
			case 'E':
			{
				Line=1;
				Column=-1;
				break;
			}
			case 'Q':
			{
				Line=-1;
				Column=0;
				break;
			}
			case 'D':
			{
				Line=1;
				Column=0;
				break;
			}
			case 'W':
			{
				Line=-1;
				Column=1;
				break;
			}
			case 'X':
			{
				Line=0;
				Column=1;
				break;
			}
			case 'C':
			{
				Line=1;
				Column=1;
				break;
			}
		}
	swap(Mat[Pos.first][Pos.second],Mat[Pos.first+Line][Pos.second+Column]);
	Pos.first+=Line;
	Pos.second+=Column;
	}//MoveToken();
	
	int Run()
	{
		unsigned NbLine = 15;
		unsigned NbColumn = 15;
		CMatrix Mat [NbLine][NbColumn];
		unsigned MaxTurn = 15;
		CPosition PosPlayer1(0, Mat.size());
		CPosition PosPlayer2(Mat.size(), 0);
		bool Win1 false;
		bool Win2 false;
		string Player1="Player1";
		string Player2="Player2";
		const string Color1=KRouge;
		const string Color2=KVert;
		
		//conf data
		
		InitMat(Mat, Nbline, NbColumn, PosPlayer1, PosPlayer2);
		//defines matrix
		ShowMatrix (Mat);
		//shows matrix
		char Move;
		for(unsigned i=0 ; i<MaxTurn ; ++i)
		{
			cin>>toupper(Move);
			MoveToken(Mat, Move, PosPlayer1);
			ShowMatrix (Mat);
			if (PosPlayer1==PosPlayer2) 
			{
				Win1=true;
				break;
			}
			//endturn Player 1
			cin>>toupper(Move);
			MoveToken(Mat, Move, PosPlayer2);
			ShowMatrix (Mat);
			if (PosPlayer2==PosPlayer1) 
			{
				Win2=true;
				break;
			}
			//endturn Player 2
		}
		if (Win1)
			cout<<Player1<<"wins"<<endl;
		else if (Win2)
			cout<<Player2<<"wins"<<endl;
		else
			cout<<"draw"<<endl;
	}
}

int main
{
	Run();
	return 0;
}
