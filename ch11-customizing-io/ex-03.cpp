#include <fstream>
#include <iostream>
using namespace std;

void error(string s1, string s2) { throw runtime_error(s1 + s2); }

int main()
{
    string ifname {"ex-03-input.txt"};
    ifstream ifs {ifname};
    if (!ifs)
        error("can't open input file ", ifname);

    for (string line; getline(ifs, line); ) {
        string s;
        for (const char& c: line) {
            if (c == 'A' || c == 'a'
                    || c == 'E' || c == 'e'
                    || c == 'I' || c == 'i'
                    || c == 'O' || c == 'o'
                    || c == 'U' || c == 'u')
                continue;
            s += c;
        }
        cout << s << '\n';
    }
    if (ifs.eof())
        return 0;

    error("something wrong with input file ", ifname);
}
