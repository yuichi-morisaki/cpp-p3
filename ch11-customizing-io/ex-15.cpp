#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void error(string s)
{ throw runtime_error(s); }

void error(string s1, string s2)
{ throw runtime_error(s1 + s2); }


int main()
try {
    string ifname {"ex-15-in.txt"};
    ifstream ifs {ifname};
    if (!ifs) error("can't open input file ", ifname);

    vector<double> vd;
    for (double d; ifs >> d; ) {
        vd.push_back(d);
    }
    if (!ifs.eof())
        error("can't reach EOF of input file ", ifname);

    for (int i = 0; i < vd.size(); ++i) {
        cout << dec << scientific << setprecision(8)
             << setw(20) << vd[i];
        if (i % 4 == 3) cout << '\n';
    }
    if ((vd.size() - 1) % 4 != 3)
        cout << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
