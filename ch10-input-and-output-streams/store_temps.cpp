#include <fstream>
#include <iostream>
using namespace std;

void error(string s1, string s2) { throw runtime_error(s1 + s2); }

double ctof(double c)
{
    return c * 9 / 5.0 + 32;
}

struct Reading {
    int hour;
    double temperature;
    char unit;
};

ostream& operator<<(ostream& os, const Reading& r)
{
    return os << r.hour << ' ' << r.temperature << r.unit;
}

int main()
try {
    string oname {"raw_temps.txt"};
    ofstream ofs {oname};
    if (!ofs)
        error("can't open output file ", oname);

    for (int h = 0; h < 24; ++h) {
        double delta = ((17 * h) % 13 + 1) / 10.0;
        double temp = (h % 3 != 0) ? 37.0 + delta : 37.0 - delta;
        Reading r {h, temp, 'c'};
        ofs << r << '\n';
    }
    for (int h = 0; h < 24; ++h) {
        double delta = ((11 * h) % 13 ) / 10.0;
        double temp = (h % 3 != 1) ? 37.0 + delta : 37.0 - delta;
        temp = ctof(temp);
        Reading r {h, temp, 'f'};
        ofs << r << '\n';
    }
    for (int h = 0; h < 24; ++h) {
        double delta = ((19 * h) % 13 ) / 10.0;
        double temp = (h % 3 != 2) ? 37.0 + delta : 37.0 - delta;
        Reading r {h, temp, 'c'};
        ofs << r << '\n';
    }

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
