#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

vector<string> split(const string& s)
{
    vector<string> vs;
    istringstream iss {s};
    for (string sub; iss >> sub; )
        vs.push_back(sub);
    if (iss.eof())
        return vs;
    throw runtime_error("istringstream is bad");
}

int main()
try {
    string s {
        "that returns a vector of whitespace-separated"
        " substrings from the argument"
    };
    vector<string> vs = split(s);
    for (const string& sub: vs)
        cout << sub << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
