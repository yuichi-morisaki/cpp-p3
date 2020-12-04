#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

void error(string s1, string s2) {
    throw runtime_error(s1 + s2);
}

int main()
try {
    string ifname1 {"ex-09-in-1.txt"};
    string ifname2 {"ex-09-in-2.txt"};
    string ofname {"ex-09-out.txt"};
    ifstream ifs1 {ifname1};
    if (!ifs1)
        error("can't open input file ", ifname1);
    ifstream ifs2 {ifname2};
    if (!ifs2)
        error("can't open input file ", ifname2);
    ofstream ofs {ofname};
    if (!ofs)
        error("can't open output file ", ofname);

    string s1;
    string s2;
    while (true) {
        if (s1 == "" && !ifs1.eof())
            ifs1 >> s1;
        if (!ifs1.eof() && (ifs1.fail() || ifs1.bad()))
            error("Failed to read from file ", ifname1);

        if (s2 == "" && !ifs2.eof())
            ifs2 >> s2;
        if (!ifs2.eof() && (ifs2.fail() || ifs2.bad()))
            error("Failed to read from file ", ifname2);

        if (s1 == "" && s2 == "")
            break;
        else if (s1 != "" && s2 == "") {
            ofs << s1 << '\n';
            s1 = "";
        }
        else if (s1 == "" && s2 != "") {
            ofs << s2 << '\n';
            s2 = "";
        }
        else {  // s1 != "" && s2 != ""
            if (s1 < s2) {
                ofs << s1 << '\n';
                s1 = "";
            }
            else {
                ofs << s2 << '\n';
                s2 = "";
            }
        }
    }

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
