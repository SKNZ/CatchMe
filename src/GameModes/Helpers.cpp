#include "Helpers.h"

using namespace Game;

void Helpers::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    int DiffX = static_cast<int> (MoveX);
    int DiffY = static_cast<int> (MoveY);
    
    if (PlayerPosition.first + DiffY >= 0 && PlayerPosition.first + DiffY < MatrixSize.first)
        PlayerPosition.first += DiffY;

    if (PlayerPosition.second + DiffX >= 0 && PlayerPosition.second + DiffX < MatrixSize.second)
        PlayerPosition.second += DiffX;
}

void ValidatePlayerPositionsNoTeam (const CPositions& PlayerPositions, unsigned CurrentPlayer, vector<bool>& PlayerLifeStates)
{
	for (unsigned i = 0; i < PlayerPositions.size (); ++i)
    {
        if (i == CurrentPlayer || !PlayerLifeStates[i])
            continue;

        if (PlayerPositions[CurrentPlayer].first == PlayerPositions[i].first
            && PlayerPositions[CurrentPlayer].second == PlayerPositions[i].second)
        {
            PlayerLifeStates[i] = false;
            break;
        }
    }
}

void LoadObstaclesFromFile (CMatrix& Matrix, std::string FileName)
{
	ifstream File (FileName);
	
	if (!File)
		throw "There was an error trying to open the file. " + FileName;

	unsigned Y, X;
	while (File >> Y >> X)
		if (Matrix.size () > Y && Matrix.begin()->size () > X)
			Matrix [Y] [X] = KTokens [KTokenObstacle];
}
