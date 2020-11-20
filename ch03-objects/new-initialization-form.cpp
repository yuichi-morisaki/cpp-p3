#include <iostream>

using namespace std;

int main()
{
    double x {2.7};
    int y {x};  // warning
    int a {1000};
    char b {a}; // warning

    return 0;
}
