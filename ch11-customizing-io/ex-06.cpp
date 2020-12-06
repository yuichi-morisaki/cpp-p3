#include <iostream>
using namespace std;

bool is_whitespace(char c, string whitespace)
{
    for (const char& w: whitespace)
        if (c == w) return true;
    return false;
}

int main()
{
    string whitespace {".;,?-'"};
    string s = "don't use the as-if rule.";

    bool quote = false;
    for (string line; getline(cin, line); ) {
        int idx = 0;
        for (char& c: line) {
            if (c == '"') {
                if (quote)
                    quote = false;
                else {
                    string::size_type p = line.find('"', idx + 1);
                    if (p != string::npos)
                        quote = true;
                }
            }

            if (!quote && is_whitespace(c, whitespace))
                c = ' ';
            ++idx;
        }
        cout << line << '\n';
    }
    if (!cin.eof() && (cin.fail() || cin.bad()))
        throw runtime_error("cin is not good");

    return 0;
}
