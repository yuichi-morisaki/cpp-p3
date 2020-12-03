#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void fill_vector(istream& is, vector<int>& v, char terminator)
{
    for (int i; is >> i; )
        v.push_back(i);

    if (is.eof())
        return;

    if (is.bad())
        throw runtime_error("istream 'is' is bad");

    if (is.fail()) {
        is.clear();     /* clear stream state
                           so that we can look for terminator */
        char c = is.get();
        if (c != terminator) {
            is.unget();
            is.clear(ios_base::failbit);    /* set the state
                                               to fail() */
        }
    }
}

int main()
try {
    vector<int> v;
    fill_vector(cin, v, '*');

    if (cin.eof()) {
        cout << "EOF\n";
        return 0;
    }
    if (cin.fail()) {
        cin.clear();
        char c = cin.get();
        cerr << "Unexpected character: '" << c << "'\n";
        return 1;
    }

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 2;
}
