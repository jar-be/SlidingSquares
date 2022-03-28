#include "cboard.h"

#include <stdexcept>
#include <algorithm>
#include <memory>

std::vector<size_t> CBoard::GetNeighbours(size_t squarePosition)
{
    std::vector<size_t> neighbours;
    auto row = squarePosition / fBoardSize;
    auto right = squarePosition + 1;
    if (right / fBoardSize == row) {
        neighbours.push_back(right);
    }
    auto left = squarePosition - 1;
    if (squarePosition > 0 && left / fBoardSize == row) {
        neighbours.push_back(left);
    }

    if (squarePosition > 0) {
        neighbours.push_back(squarePosition - fBoardSize);
    }

    auto down = squarePosition + fBoardSize;
    if (down < fBoardState.size()) {
        neighbours.push_back(down);
    }

    return neighbours;
}

CBoard::CBoard(int boardSize) : fBoardSize(boardSize), fMoveCount(0)
{
    if (boardSize < 3) {
        throw std::invalid_argument("boardSize must be greater than 2");
    }

    int piecesCount = boardSize * boardSize;
    fBoardState.reserve(piecesCount);
    for (int idx = 0; idx < piecesCount - 1; ++idx) {
        fBoardState.push_back(std::make_unique<CSquare>(idx, false, std::to_string(idx)));
    }
    int emptyPieceIndex = piecesCount - 1;
    fBoardState.push_back(std::make_unique<CSquare>(emptyPieceIndex, true, std::to_string(emptyPieceIndex)));
}

void CBoard::Move(size_t squarePosition)
{
    if (squarePosition >= fBoardState.size()) {
        throw new std::out_of_range("squarePosition is out of range");
    }

    if (at(squarePosition).IsEmpty()) {
        throw new std::invalid_argument("Square at squarePosition is empty");
    }

    auto neighbours = GetNeighbours(squarePosition);
    auto empty = std::find_if(neighbours.begin(),
                              neighbours.end(),
                              [this](auto idx) { return at(idx).IsEmpty(); });
    if (empty == neighbours.end()) {
        throw new std::invalid_argument("Square at squarePosition is not next to an empty square");
    }

    auto emptyIdx = *empty;
    fBoardState[squarePosition].swap(fBoardState[emptyIdx]);
}

const CSquare& CBoard::at(std::size_t squarePosition) const
{
    return *(fBoardState.at(squarePosition));
}
