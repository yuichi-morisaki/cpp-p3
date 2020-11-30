#include <iostream>
#include <vector>
using namespace std;

vector<int> map_to_num_of_chars(const vector<string>& vs)
{
    vector<int> vi;
    for (string s: vs) {
        vi.push_back(s.size());
    }

    return vi;
}

class Length {
    public:
        string longest;
        string shortest;
        Length(string l, string s)
            : longest {l}, shortest {s} { }
};

Length scan_length(const vector<string>& vs)
{
    if (vs.size() == 0)
        throw runtime_error("Empty vector");

    string shortest = vs[0];
    string longest = vs[0];
    for (string s: vs) {
        if (s.size() < shortest.size()) shortest = s;
        if (s.size() > longest.size()) longest = s;
    }
    return Length(longest, shortest);
}

class LexOrder {
    public:
        string first;
        string last;
        LexOrder(string f, string l)
            : first {f}, last {l} { }
};

LexOrder scan_lex_order(const vector<string>& vs)
{
    if (vs.size() == 0)
        throw runtime_error("Empty vector");

    string first = vs[0];
    string last = vs[0];
    for (string s: vs) {
        if (s < first) first = s;
        if (s > last) last = s;
    }
    return LexOrder(first, last);
}

int main()
{
    vector<string> vs = {"abcde", "foobazbar", "!", "xyz"};

    vector<int> vi = map_to_num_of_chars(vs);
    for (int i: vi) cout << i << ' ';
    cout << '\n';

    Length len = scan_length(vs);
    cout << len.shortest << ", " << len.longest << '\n';

    LexOrder lex = scan_lex_order(vs);
    cout << lex.first << ", " << lex.last << '\n';

    return 0;
}
