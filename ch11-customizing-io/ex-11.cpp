#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

bool is_whitespace(const char& c, const string& ws)
{
    for (const char& w: ws)
        if (c == w) return true;
    return false;
}

vector<string> split(const string& s, const string& w)
{
    vector<string> vs;
    istringstream iss1 {s};
    for (string sub1; iss1 >> sub1; ) {
        for (char& c: sub1)
            if (is_whitespace(c, w)) c = ' ';
        istringstream iss2 {sub1};
        for (string sub2; iss2 >> sub2; )
            vs.push_back(sub2);
        if (!iss2.eof())
            throw runtime_error("iss2 is bad");
    }
    if (!iss1.eof())
        throw runtime_error("iss1 is bad");
    return vs;
}

int main()
try {
    string s {
        "Write a function;"
        " that returns a vector of whitespace-separated"
        " substrings, from the argument s."
    };
    string w {".,:;-"};
    vector<string> vs = split(s, w);
    for (const string& sub: vs)
        cout << sub << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
