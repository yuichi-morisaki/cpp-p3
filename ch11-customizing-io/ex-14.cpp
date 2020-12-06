#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

void error(string s1, string s2)
{ throw runtime_error(s1 + s2); }

int main()
try {
    string ifname {"ex-14.cpp"};
    ifstream ifs {ifname};
    if (!ifs) error("can't open input file ", ifname);

    int nspace = 0;
    int nalpha = 0;
    int ndigit = 0;
    int npunct = 0;
    for (char c; ifs.get(c); ) {
        if (isspace(c)) ++nspace;
        if (isalpha(c)) ++nalpha;
        if (isdigit(c)) ++ndigit;
        if (ispunct(c)) ++npunct;
    }
    if (!ifs.eof())
        error("can't reach EOF of input file ", ifname);

    cout << "space: " << nspace << '\n'
         << "alpha: " << nalpha << '\n'
         << "digit: " << ndigit << '\n'
         << "punct: " << npunct << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
