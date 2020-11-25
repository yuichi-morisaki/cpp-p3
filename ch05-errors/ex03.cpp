#include <iostream>
#include <stdexcept>

using namespace std;

double ctok(double c)
{
    /* move into main()
    if (c < -273.15)
        throw runtime_error("Invalid arg in ctok()");
    */

//    int k = c + 273.15;
    double k = c + 273.15;

    if (k < 0)
        throw runtime_error("Invalid result in ctok()");

//    return int
    return k;
}

int main()
try {
    double c = 0;
//    cin >> d;
    cin >> c;

    if (!cin)
        throw runtime_error("Failed to read input temperature");

    if (c < -273.15)
        throw runtime_error("Invalid temperature: below -273.15 degree Celsius");
//    double k = ctok("c");
    double k = ctok(c);

//    Cout << k << '\n';
    cout << k << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Fatal: unknown error was detected.\n";
    return 2;
}
