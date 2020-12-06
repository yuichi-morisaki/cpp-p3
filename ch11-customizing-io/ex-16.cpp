#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void error(string s1, string s2)
{ throw runtime_error(s1 + s2); }


int main()
try {
    string ifname {"ex-16-in.txt"};
    ifstream ifs {ifname};
    if (!ifs) error("can't open input file ", ifname);

    vector<double> vd;
    for (double d; ifs >> d; )
        vd.push_back(d);
    if (!ifs.eof())
        error("can't reach EOF of input file ", ifname);

    sort(vd.begin(), vd.end());

    int cnt = 1;
    for (int i = 0; i < vd.size(); ++i) {
        if (i == vd.size()-1 || vd[i] != vd[i+1]) {
            if (cnt == 1)
                cout << vd[i] << '\n';
            else
                cout << vd[i] << '\t' << cnt << '\n';
            cnt = 1;
        }
        else {
            ++cnt;
        }
    }

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
