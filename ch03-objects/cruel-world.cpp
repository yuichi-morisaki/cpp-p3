#include <iostream>

using namespace std;

int Main()  // detected at link time
{
    STRING s = "Goodbye, cruel world!";  // detected at compile time
    // string s = "Goodbye, cruel world!";
    cOut << S << '\n';   // detected at compile time
    // cout << s << '\n';

    return 0;
}
