#include "cboard.h"

#include <stdexcept>

CBoard::CBoard(int boardSize) : fBoardSize(boardSize), fMoveCount(0)
{
    int piecesCount = boardSize * boardSize;
    fBoardState.reserve(fBoardSize);
    for (int idx = 0; idx < piecesCount - 1; ++idx) {
        fBoardState.push_back(std::make_unique<CSquare>(idx, false, std::to_string(idx)));
    }
    int emptyPieceIndex = piecesCount - 1;
    fBoardState.push_back(std::make_unique<CSquare>(emptyPieceIndex, true, std::to_string(emptyPieceIndex)));
}

const CSquare& CBoard::at(std::size_t squarePosition) const
{
    return *(fBoardState.at(squarePosition));
}
