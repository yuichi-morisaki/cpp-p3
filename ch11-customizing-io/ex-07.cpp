#include <iostream>
#include <locale>
#include <vector>
using namespace std;

bool is_whitespace(char c)
{
    string whitespace = ".;,?'";
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
    /*
        Modify the program from the previous exercise so that
        it replaces don't with do not, can't with cannot, etc.;
        leaves hyphens within words intact; and converts all
        characters to lower case.
    */

    vector<string> abbr {
        "can't", "Can't", "don't", "Don't"
    };
    vector<string> not_abbr {
        "cannot", "Cannot", "do not", "Do not"
    };

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

            if (c == '-') { /* -abc abc-def def- */
                if (!isalpha(line[idx - 1])
                        || !isalpha(line[idx + 1]))
                    c = ' ';
            }
            if (!quote) {
                if (is_whitespace(c))
                    c = ' ';
            }
            c = tolower(c);
            ++idx;
        }
        cout << line << '\n';
    }

    return 0;
}
