#include <iostream>
#include "cboard.h"

using namespace std;

int main()
{
    CBoard cb(4);
    cout << "Hello World! " << cb.at(15).DisplayName() << endl;
    return 0;
}
