#include <fstream>

#include "Helpers.h"

using namespace Game;

void Helpers::MovePlayer (const CMatrix& Matrix, CPosition& PlayerPosition, const CPosition& MatrixSize, const PlayerMovesY MoveY, const PlayerMovesX MoveX)
{
    int DiffY = static_cast<int> (MoveY);
    int DiffX = static_cast<int> (MoveX);

    if (PlayerPosition.first + DiffY < 0 || PlayerPosition.first + DiffY >= MatrixSize.first)
        DiffY = 0;

    if (PlayerPosition.second + DiffX < 0 || PlayerPosition.second + DiffX >= MatrixSize.second)
        DiffX = 0;

    if (PlayerPosition.first + DiffY > 0 && PlayerPosition.second + DiffX > 0
        && PlayerPosition.first + DiffY < MatrixSize.first && PlayerPosition.second + DiffX < MatrixSize.second)
    {
        if (Matrix [PlayerPosition.first + DiffY] [PlayerPosition.second + DiffX] == KTokens [KTokenObstacle]) // Is direct movement impossbru ? Try to keep just X or Y movement
        {
            if (Matrix [PlayerPosition.first + DiffY] [PlayerPosition.second] == KTokens [KTokenObstacle])
                DiffY = 0;

            if (Matrix [PlayerPosition.first] [PlayerPosition.second + DiffX] == KTokens [KTokenObstacle])
                DiffX = 0;
        }
    }

    PlayerPosition.first += DiffY;
    PlayerPosition.second += DiffX;
}

void Helpers::ValidatePlayerPositionsNoTeam (const CPositions& PlayerPositions, unsigned CurrentPlayer, std::vector<bool>& PlayerLifeStates)
{
	for (unsigned i = 0; i < PlayerPositions.size (); ++i)
    {
        if (i == CurrentPlayer || !PlayerLifeStates[i])
            continue;

        if (PlayerPositions [CurrentPlayer].first == PlayerPositions [i].first
            && PlayerPositions [CurrentPlayer].second == PlayerPositions [i].second)
        {
            PlayerLifeStates[i] = false;
            break;
        }
    }
}

void Helpers::LoadObstaclesFromFile (CMatrix& Matrix, std::string FileName)
{
	std::ifstream File (FileName);
	
	if (!File)
    {
        return; // @todo Remove this once every file was created and populated
		throw std::runtime_error("There was an error trying to open the file: " + FileName);
    }

	unsigned Y, X;
	while (File >> Y >> X)
		if (Matrix.size () > Y && Matrix.begin()->size () > X)
			Matrix [Y] [X] = KTokens [KTokenObstacle];
}
