#include "chrono.h"
#include <iostream>

using namespace std;

void f(int y)
{
    bool ly = Chrono::leapyear(y);
    if (ly)
        cout << y << " is a leap year\n";
    else
        cout << y << " is not a leap year\n";
}

int main()
{
    f(1995);
    f(1996);
    f(2000);
    f(2100);
}
