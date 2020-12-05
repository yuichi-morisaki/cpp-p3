#include <fstream>
#include <iostream>
using namespace std;

void error(string s1, string s2) { throw runtime_error(s1 + s2); }

int main()
{
    string name {"example-data-for-positioning.txt"};
    fstream fs {name};
    if (!fs)
        error("can't open ", name);

    fs.seekg(5);    // seek for get
    char ch;
    fs >> ch;
    cout << "character[5] is " << ch << '(' << int(ch) << ")\n";

    fs.seekp(1);    // seek for put
    fs << 'y';
}
