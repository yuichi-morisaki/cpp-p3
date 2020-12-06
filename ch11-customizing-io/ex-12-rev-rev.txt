#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

void error(string s1, string s2)
{ throw runtime_error(s1 + s2); }

void reverse(const string& ifname, const string& ofname)
{
    ifstream ifs {ifname};
    if (!ifs) error("can't open input file ", ifname);
    ofstream ofs {ofname};
    if (!ofs) error("can't open output file ", ofname);

    vector<string> vec;
    string line;
    for (char c; ifs.get(c); ) {
        line += c;
        if (c == '\n') {
            vec.push_back(line);
            line = "";
        }
    }
    if (!ifs.eof())
        error("Not reach EOF, ", ifname);
    if (line != "")
        vec.push_back(line);

    for (int i = vec.size() - 1; i >= 0; --i) {
        line = vec[i];
        for (int j = line.size() - 1; j >= 0; --j)
            ofs.put(line[j]);
    }
}

int main()
try {
    string ifname {"ex-12.cpp"};
    string ofname {"ex-12-rev.txt"};
    reverse(ifname, ofname);

    ifname = ofname;
    ofname = "ex-12-rev-rev.txt";
    reverse(ifname, ofname);

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
