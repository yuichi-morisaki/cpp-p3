#include <iostream>

using namespace std;

int main()
{
    double d = 0;
    cin >> d;
    if (cin) {
        // all is well, and we can try reading again
    } else {
        // the last read didn't succeed, so we take some other action
        cerr << "couldn't read a double\n";
        return 1;
    }

    return 0;
}
