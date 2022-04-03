#ifndef CBOARD_H
#define CBOARD_H

#include <vector>
#include <memory>
#include <iostream>
#include "SlidingSquaresLib_global.h"
#include "cshuffler.h"
#include "csquare.h"

/**
 * \class CBoard
 * @brief The CBoard class contains the puzzle board
 */
class SLIDINGSQUARESLIB_EXPORT CBoard
{
    typedef std::vector<std::unique_ptr<CSquare>> boardType;
    int fBoardSize; //!< Board size
    boardType fBoardState; //!< The state of the board
    int fMoveCount; //!< How many moves were made
    size_t fEmptySquareIndex; //!< Index of the empty square

    /**
     * @brief GetNeighbours returns the indexes of the neighbours of the square
     * @param squarePosition Find neighbours of the given square
     * @return Array of indexes of neighbours
     */
    std::vector<size_t> get_neighbours(size_t squarePosition);
public:
    /**
     * @brief Board constructor
     * @param boardSize - size of the board (contains boardSize * boardSize squares)
     * @exception invalid_argument boardSize must be greater than 2
     */
    CBoard(int boardSize);

    /**
     * @brief Shuffle the board.
     *
     * It would be tricky to generate the board, so we generate an ordered board and
     * then shuffle it by randomly moving the pieces.
     * @see https://mathworld.wolfram.com/15Puzzle.html
     * @param shuffler The shuffler object to use
     * @param moves Number of moves to make
     */
    void shuffle(CShuffler &shuffler, int moves);

    /**
     * @brief Moves the square to an empty square (square has to be next to an empty spot)
     * @param squarePosition The position of the square to move
     * @return new position of the moved square
     * @exception invalid_argument Square is not next to an empty spot
     * @exception out_of_range Given position it out of range
     */
    size_t move(size_t squarePosition);

    /**
     * @brief Returns the square at the given position
     * @param squarePosition The position of the square to get
     * @return CSquare at the given position
     * @exception out_of_range Given position it out of range
     */
    const CSquare& at(size_t squarePosition) const;

    /**
     * @brief Get the move count
     * @return How many moves were made
     */
    int moveCount() const { return fMoveCount; }

    /**
     * @brief Get EmptySquareIndex
     * @return Index of the empty square
     */
    size_t empty_square_index() const { return fEmptySquareIndex; }

    boardType::const_iterator begin() const { return fBoardState.begin(); }
    boardType::const_iterator end() const { return fBoardState.end(); }
    bool is_at_correct_place(std::size_t squarePosition) const;
    bool is_solved() const;

    friend std::ostream& operator<<(std::ostream& os, const CBoard& v) {
        int row = 0;
        int idx = 0;
        for (const auto &s : v.fBoardState) {
            if (idx / v.fBoardSize != row) {
                row = idx / v.fBoardSize;
                os << std::endl;
            }
            os << (s->is_empty() ? "[ ]" : s->displayName()) << "\t";
            ++idx;
        }
        os << std::endl;
        return os;
    }
};

#endif // CBOARD_H
