#include <algorithm>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>
using namespace std;

bool is_whitespace(char c)
{
    string whitespace = ".:;,?'";
    for (const char& w: whitespace)
        if (c == w) return true;
    return false;
}

string::size_type contains(string s, string sub)
{
    if (sub.size() == 0)
        throw runtime_error("contains: substring is empty");
    string::size_type p = s.find(sub[0]);
    while (p != string::npos) {
        if (sub == s.substr(p, sub.size()))
            return p;
        p = s.find(sub[0], p + 1);
    }
    return p;
}

int main()
{

    vector<string> abbr {
        "can't", "Can't", "don't", "Don't"
    };
    vector<string> not_abbr {
        "cannot", "Cannot", "do not", "Do not"
    };
    vector<string> vs;

    bool quote = false;
    for (string line; getline(cin, line); ) {
        for (int i = 0; i < abbr.size(); ++i) {
            string::size_type p = contains(line, abbr[i]);
            if (p != string::npos)
                line.replace(p, abbr[i].size(), not_abbr[i]);
        }

        int idx = 0;
        for (char& c: line) {
            if (c == '"') {
                if (quote)
                    quote = false;
                else {
                    string::size_type p = line.find('"', idx + 1);
                    if (p != string::npos) quote = true;
                }
            }

            if (c == '-') {
                char p = line[idx - 1];
                char n = line[idx + 1];
                if (!isalpha(p) || !isalpha(n)) c = ' ';
            }

            if (!quote && is_whitespace(c)) c = ' ';

            c = tolower(c);
            ++idx;
        }

        istringstream iss {line};
        for (string word; iss >> word; )
            vs.push_back(word);
    }

    sort(vs.begin(), vs.end());
    for (int i = 0; i < vs.size(); ++i)
        if (i == 0 || vs[i] != vs[i-1])
            cout << vs[i] << '\n';

    return 0;
}
