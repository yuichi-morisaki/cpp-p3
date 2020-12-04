#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

void error(string s) { throw runtime_error(s); }
void error(string s1, string s2) { throw runtime_error(s1 + s2); }

int main()
try {
    string iname {"ex-01.txt"};
    ifstream ifs {iname};
    if (!ifs)
        error("can't open input file ", iname);

    int sum = 0;
    for (int i; ifs >> i && cin; ) {
        sum += i;
    }
    if (ifs.eof())
        cout << "sum is " << sum << '\n';
    else if (ifs.fail()) {
        cout << "sum is " << sum << '\n';
        error("failed to read an integer");
    }
    else {  // ifs.bad()
        cout << "sum is " << sum << '\n';
        error("Bad input");
    }

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
