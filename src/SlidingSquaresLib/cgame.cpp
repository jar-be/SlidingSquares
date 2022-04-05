#include "cgame.h"
#include "cgamestats.h"
#include "crandomshuffler.h"
#include <stdexcept>

CGame::CGame()
    : move_count(0)
{

}

CGameStats CGame::get_game_stats() const
{
    return CGameStats(move_count, stop_watch.get_duration());
}

void CGame::new_game(int size)
{
    move_count = 0;
    board = std::make_unique<CBoard>(size);
}

void CGame::shuffle()
{
    if (board == nullptr) {
        throw std::logic_error("Game not started");
    }
    auto size = board->boardSize();
    int shuffleCount = size * size * size;
    CRandomShuffler shuffler;
    board->shuffle(shuffler, shuffleCount);
}

std::string CGame::get_display_name(size_t index) const
{
    if (board == nullptr) {
        throw std::logic_error("Game not started");
    }
    auto square = board->at(index);
    return square.is_empty() ? "" : square.displayName();
}

bool CGame::is_at_correct_place(std::size_t squarePosition) const
{
    if (board == nullptr) {
        throw std::logic_error("Game not started");
    }
    auto square = board->at(squarePosition);
    return (size_t)square.id() == squarePosition;
}

size_t CGame::move(size_t squarePosition)
{
    if (board == nullptr) {
        throw std::logic_error("Game not started");
    }
    if (move_count == 0) {
        stop_watch.start();
    }
    ++move_count;
    auto new_square_position = board->move(squarePosition);
    if (board->is_solved()) {
        stop_watch.stop();
    }
    return new_square_position;
}

bool CGame::is_solved() const
{
    if (board == nullptr) {
        throw std::logic_error("Game not started");
    }
    return board->is_solved();
}
