#pragma once

#include <vector>
#include <utility>

namespace Game
{
    typedef std::vector<char>       CLine;
    typedef std::vector<CLine>      CMatrix;
    typedef std::pair<int, int>     CPosition;
    typedef std::vector<CPosition>  CPositions;

    // Constants
    const std::pair<int, int> RenderMatrixSize = { 10, 20 }; // X, Y

    int Run ();
}