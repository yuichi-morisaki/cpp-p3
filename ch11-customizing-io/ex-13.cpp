#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

void error(string s1)
{ throw runtime_error(s1); }

void error(string s1, string s2)
{ throw runtime_error(s1 + s2); }


int main()
{
    string ifname {"ex-13.cpp"};
    ifstream ifs {ifname};
    if (!ifs) error("can't open input file ", ifname);

    string ofname {"ex-13-out.txt"};
    ofstream ofs {ofname};
    if (!ofs) error("can't open output file ", ofname);

    vector<string> vs;
    string line {};
    for (char c; ifs.get(c); ) {
        if (c == '\n') {
            vs.push_back('\n' + line);
            line = "";
            continue;
        }

        if (isspace(c))
            line += c;
        else {
            ifs.unget();
            string s;
            ifs >> s;
            for (int i = s.size() - 1; i >= 0; --i)
                line += s[i];
        }
    }
    if (!ifs.eof())
        error("can't reach EOF");
    if (line != "")
        vs.push_back('\n' + line);

    for (string line: vs)
        for (int i = line.size() - 1; i >= 0; --i)
            ofs.put(line[i]);

    return 0;
}
