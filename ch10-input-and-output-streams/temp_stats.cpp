#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void error(string s) { throw runtime_error(s); }
void error(string s1, string s2) { throw runtime_error(s1 + s2); }

struct Reading {
    int hour;
    double temperature;
    char unit;
};

ostream& operator<<(ostream& os, const Reading& r)
{
    return os << r.hour << ' ' << r.temperature << r.unit;
}

double ftoc(double f)
{
    return 5 * (f - 32) / 9.0;
}

double ctof(double c)
{
    return c * 9 / 5.0 + 32;
}

istream& operator>>(istream& is, Reading& r)
{
    int hour;
    double temp;
    char unit;
    is >> hour >> temp >> unit;
    if (!is)
        error("bad input");

    if (hour < 0 || 23 < hour)
        error("hour - out of range");

    if (unit == 'f')
        r.temperature = temp;
    else if (unit == 'c')
        r.temperature = ctof(temp);
    else
        error("Unknown unit; ", to_string(unit));

    r.hour = hour;
    r.unit = 'f';

    return is;
}

bool operator==(const Reading& a, const Reading& b)
{
    return a.hour == b.hour
        && a.temperature == b.temperature
        && a.unit == b.unit;
}

bool operator!=(const Reading& a, const Reading& b)
{
    return !(a == b);
}

bool operator<(const Reading& a, const Reading& b)
{
    double temp_a;
    switch (a.unit) {
        case 'f':
            temp_a = a.temperature;
            break;
        case 'c':
            temp_a = ctof(a.temperature);
            break;
        default:
            error("Unknown unit: ", to_string(a.unit));
    }

    double temp_b;
    switch (b.unit) {
        case 'f':
            temp_b = b.temperature;
            break;
        case 'c':
            temp_b = ctof(b.temperature);
            break;
        default:
            error("Unknown unit: ", to_string(b.unit));
    }

    return temp_a < temp_b
        || (temp_a == temp_b) && a.hour < b.hour
        || (temp_a == temp_b)
            && a.hour == b.hour && a.unit < b.unit;
}

int main()
try {
    string iname {"raw_temps.txt"};
    ifstream ifs {iname};
    if (!ifs)
        error("can't open input file ", iname);

    vector<Reading> readings;
    while (ifs) {
        char c;
        ifs >> c;
        if (ifs.eof())
            break;
        ifs.unget();

        Reading r;
        ifs >> r;
        if (ifs)
            readings.push_back(r);
    }
    if (!ifs.eof() && (ifs.fail() || ifs.bad()))
        error("failed to read input");

    if (readings.size() == 0) {
        cout << "Empty date\n";
        return 0;
    }

    double sum = 0;
    for (const Reading& r: readings) {
        sum += r.temperature;
    }
    double mean = sum / readings.size();
    cout << "mean: " << mean << "[f] == "
         << ftoc(mean) << "[c]\n";

    sort(readings.begin(), readings.end());
    int idx = readings.size() / 2;
    double median = 0;
    if (readings.size() % 2)
        median = (readings[idx - 1].temperature
                    + readings[idx].temperature) / 2;
    else
        median = readings[idx].temperature;

    cout << "median: " << median << "[f] == "
         << ftoc(median) << "[c]\n";

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
