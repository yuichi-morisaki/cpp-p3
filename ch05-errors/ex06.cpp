#include <iostream>
#include <stdexcept>

using namespace std;

constexpr double MIN_C = -273.15;
constexpr double MIN_F = -273.15 * 9 / 5 + 32;

double ctof(double c)
{
    if (c < MIN_C)
        throw runtime_error("Invalid arg in ctof(): below absolute zero");
    double f = c * 9 / 5 + 32;
    if (f < MIN_F)
        throw runtime_error("Invalid result in ctof(): below absolute zero");
    return f;
}

double ftoc(double f)
{
    if (f < MIN_F)
        throw runtime_error("Invalid arg in ftoc(): below absolute zero");
    double c = (f - 32) * 5 / 9.0;
    if (c < MIN_C)
        throw runtime_error("Invalid result in ftoc(): below absolute zero");
    return c;
}

int main()
try {
    string prompt = "Enter a temperature followed by unit [c/f]: ";
    double temp;
    char unit;
    cout << prompt;
    while (cin >> temp >> unit)
    {
        if (temp == 0 && unit == 'q')
            break;
        double c, f;
        switch (unit)
        {
            case 'c':
                f = ctof(temp);
                cout << temp << " [c] == " << f << " [f]\n";
                break;
            case 'f':
                c = ftoc(temp);
                cout << temp << " [f] == " << c << " [c]\n";
                break;
            default:
                cout << "Sorry, I don't know a unit: '" << unit << "'\n";
                break;
        }
        cout << prompt;
    }
    if (!cin)
        throw runtime_error("Failed to read input");

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
