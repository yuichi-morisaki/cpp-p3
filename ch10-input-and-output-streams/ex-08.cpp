#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

void error(string s1, string s2) { throw runtime_error(s1 + s2); }


int main()
try {
    string iname1;
    cout << "Enter a name for first input file: ";
    cin >> iname1;
    ifstream ifs1 {iname1};
    if (!ifs1)
        error("can't open input file ", iname1);

    string iname2;
    cout << "Enter a name for second input file: ";
    cin >> iname2;
    ifstream ifs2 {iname2};
    if (!ifs2)
        error("can't open input file ", iname2);

    string oname;
    cout << "Enter a name for output file: ";
    cin >> oname;
    ofstream ofs {oname};
    if (!ofs)
        error("can't open output file ", oname);

    char c;
    while (ifs1) {
        c = ifs1.get();
        if (ifs1.eof()) break;
        if (ifs1.fail() || ifs1.bad())
            error("Failed to read from file ", iname1);
        ofs.put(c);
        if (ofs.fail() || ofs.bad())
            error("Failed to write into file ", oname);
    }
    while (ifs2) {
        c = ifs2.get();
        if (ifs2.eof()) break;
        if (ifs2.fail() || ifs2.bad())
            error("Failed to read from file ", iname2);
        ofs.put(c);
        if (ofs.fail() || ofs.bad())
            error("Failed to write into file ", oname);
    }

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
