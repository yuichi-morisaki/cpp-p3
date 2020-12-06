#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

void error(string s) { throw runtime_error(s); }
void error(string s1, string s2) {
    throw runtime_error(s1 + s2);
}

struct EOF_exception {};

void skip_to_int(ifstream& ifs)
{
    if (ifs.fail()) {
        ifs.clear();
        char c;
        while (true) {
            ifs >> c;
            if (ifs.eof())
                throw EOF_exception {};
            if (ifs.bad())
                error("ifs is bad");
            if (ifs.fail())
                error("ifs is fail");
            if (isdigit(c) || c == '-')
                break;
        }
        ifs.unget();
        return;
    }
}

int get_int(ifstream& ifs)
{
    int n = 0;
    while (true) {
        if (ifs >> n)
            return n;
        if (ifs.eof()) {
            throw EOF_exception {};
        }
        if (ifs.bad())
            error("ifstream is bad");
        skip_to_int(ifs);
    }
}

int main()
try {
    string fname {"ex-11-in.txt"};
    ifstream ifs {fname};
    if (!ifs)
        error("can't open input file ", fname);

    int sum = 0;
    int n = 0;
    while (true) {
        try {
            n = get_int(ifs);
            sum += n;
        }
        catch (EOF_exception& e) {
            break;
        }
    }

    cout << sum << '\n';
    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
