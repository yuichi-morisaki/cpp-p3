#include <iostream>
#include <stdexcept>

using namespace std;

double ctok(double c)
{
    if (c < -273.15)
        throw runtime_error("Invalid arg in ctok()");

//    int k = c + 273.15;
    double k = c + 273.15;

    if (k < 0)
        throw runtime_error("Invalid result in ctok()");

//    return int
    return k;
}

double ktoc(double k)
{
    if (k < 0)
        throw runtime_error("Invalid arg in ktoc()");
    double c = k - 273.15;
    if (c < -273.15)
        throw runtime_error("Invalid result in ctok()");
    return c;
}

int main()
try {
    cout << "Enter a temperature in celsius: ";
    double c = 0;
//    cin >> d;
    cin >> c;

    if (!cin)
        throw runtime_error("Failed to read input temperature");

//    double k = ctok("c");
    double k = ctok(c);
//    Cout << k << '\n';
    cout << k << '\n';

    cout << "Enter a temperature in kelvin: ";
    cin >> k;
    if (!cin)
        throw runtime_error("Failed to read input temperature");
    c = ktoc(k);
    cout << c << '\n';

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
