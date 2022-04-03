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

    if (squarePosition >= (size_t)fBoardSize) {
        auto up = squarePosition - fBoardSize;
        neighbours.push_back(up);
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

    fEmptySquareIndex = emptyPieceIndex;
}

void CBoard::Shuffle(CShuffler &shuffler, int moves)
{
    for (int i = 0; i < moves; ++i) {
        auto emptyNeighbours = GetNeighbours(fEmptySquareIndex);
        auto squareToMove = shuffler.PickMove(emptyNeighbours);
        Move(squareToMove);
    }
}

size_t CBoard::Move(size_t squarePosition)
{
    if (squarePosition >= fBoardState.size()) {
        throw std::out_of_range("squarePosition is out of range");
    }

    if (at(squarePosition).IsEmpty()) {
        throw std::invalid_argument("Square is empty");
    }

    auto neighbours = GetNeighbours(squarePosition);

    if (!std::any_of(
                neighbours.begin(),
                neighbours.end(),
                [this](auto idx) { return idx == fEmptySquareIndex; })) {
        throw std::invalid_argument("Square is not next to an empty square");
    }

    fBoardState[squarePosition].swap(fBoardState[fEmptySquareIndex]);
    auto newPosition = fEmptySquareIndex;
    fEmptySquareIndex = squarePosition;
    ++fMoveCount;
    return newPosition;
}

const CSquare& CBoard::at(std::size_t squarePosition) const
{
    return *(fBoardState.at(squarePosition));
}

bool CBoard::isAtCorrectPlace(std::size_t squarePosition) const
{
    return (size_t)fBoardState.at(squarePosition)->Id() == squarePosition;
}

bool CBoard::isSolved() const {
    for (size_t i = 0; i < fBoardState.size(); ++i) {
        if (!isAtCorrectPlace(i)) {
            return false;
        }
    }
    return true;
}
