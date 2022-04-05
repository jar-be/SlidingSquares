#ifndef CGAME_H
#define CGAME_H

#include "SlidingSquaresLib_global.h"
#include "cboard.h"
#include "cgamestats.h"
#include "cstopwatch.h"
#include <string>
#include <memory>

class SLIDINGSQUARESLIB_EXPORT CGame
{
    std::unique_ptr<CBoard> board;
    CStopwatch stop_watch;
    int move_count;
public:
    enum shuffler_t { random, random_with_mem, always_min };
    CGame();
    CGameStats get_game_stats() const;
    void new_game(int size);
    void shuffle();
    void shuffle(shuffler_t shuffler);
    bool is_at_correct_place(std::size_t squarePosition) const;
    size_t move(size_t squarePosition);
    std::string get_display_name(size_t index) const;
    bool is_solved() const;
private:
    void shuffle(CShuffler &shuffler);
};

#endif // CGAME_H
