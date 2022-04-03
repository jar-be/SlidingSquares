#include <crandomshuffler.h>
#include <iostream>
#include "cboard.h"

using namespace std;

int main()
{
    CBoard cb(4);
    cout << cb;
    cout << endl;

    CRandomShuffler shuffler;
    cb.shuffle(shuffler, 1000);
    cout << cb;
    cout << endl;

    return 0;
}
