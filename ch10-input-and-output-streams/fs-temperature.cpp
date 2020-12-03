#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
using namespace std;

void error(string s);
void error(string s1, string s2);

struct Reading {
    int hour;
    double temperature;
};

int main()
{
    string iname;
    cout << "Please enter input file name: ";
    cin >> iname;
    ifstream is {iname};
    if (!is)
        error("can't open input file ", iname);

    string oname;
    cout << "Please enter name of output file: ";
    cin >> oname;
    ofstream os {oname};
    if (!os)
        error("can't open output file ", oname);

    vector<Reading> temps;
    int hour;
    double temperature;
    while (is >> hour >> temperature) {
        if (hour < 0 || 23 < hour)
            error("hour out of range");
        temps.push_back(Reading {hour, temperature});
    }

    for (int i = 0; i < temps.size(); ++i)
        os << '(' << temps[i].hour << ','
            << temps[i].temperature << ")\n";

    return 0;
}


void error(string s)
{
    throw runtime_error(s);
}

void error(string s1, string s2)
{
    throw runtime_error(s1 + s2);
}
