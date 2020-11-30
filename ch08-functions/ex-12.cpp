#include <iostream>
#include <vector>
using namespace std;

void print_until_s(vector<string> v, string quit)
{
    for (string s: v) {
        if (s == quit)
            return;
        cout << s << '\n';
    }
}

bool print_until_s_improved(const vector<string>& v, string quit)
{
    for (string s: v) {
        if (s == quit)
            return true;
        cout << s << '\n';
    }
    return false;
}

bool print_until_ss(const vector<string>& v, string quit)
{
    bool found = false;
    for (string s: v) {
        if (s == quit) {
            if (found)
                return true;
            found = true;
        }
        cout << s << '\n';
    }
    return false;
}

int main()
{
    string quit = "quit";
    vector<string> v1 = {"foo", "bar", "baz", "quit"};
    vector<string> v2 = {"foo", "bar", "baz"};

    cout << "\nOriginal version\n";
    cout << "-- v1 --\n";
    print_until_s(v1, quit);
    cout << "-- v2 --\n";
    print_until_s(v2, quit);

    cout << "\nImproved version\n";
    cout << "-- v1 --\n";
    bool found1 = print_until_s_improved(v1, quit);
    if (found1)
        cout << '\t' << "End with " << quit << '\n';
    cout << "-- v2 --\n";
    bool found2 = print_until_s_improved(v2, quit);
    if (found2)
        cout << '\t' << "End with " << quit << '\n';

    cout << "\nprint_until_ss\n";
    vector<string> v3 = {"foo", "quit", "bar", "baz", "quit", "hoge"};
    print_until_ss(v3, quit);

    return 0;
}
