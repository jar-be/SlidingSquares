#include <iostream>
#include "cboard.h"

using namespace std;

void print_board(const CBoard& cb)
{
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            auto square = cb.at(i*4 + j);
            cout << (square.IsEmpty() ? "[ ]" : square.DisplayName()) << "\t";
        }
        cout << endl;
    }
}

int main()
{
    CBoard cb(4);
    print_board(cb);
    cout << endl;

    cb.Move(14);
    print_board(cb);
    cout << endl;

    cb.Move(10);
    print_board(cb);

    return 0;
}
