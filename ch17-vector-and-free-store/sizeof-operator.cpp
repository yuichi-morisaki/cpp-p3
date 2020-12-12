#include <iostream>
#include <vector>
using namespace std;

void sizes(char ch, int i, int* p, bool b, double d) {
    cout << "the size of char is "
         << sizeof(char) << ' ' << sizeof(ch) << '\n';
    cout << "the size of int is  "
         << sizeof(int) << ' ' << sizeof(i) << '\n';
    cout << "the size of int* is "
         << sizeof(int*) << ' ' << sizeof(p) << '\n';
    cout << "the size of bool is "
         << sizeof(bool) << ' ' << sizeof(b) << '\n';
    cout << "the size of double is "
         << sizeof(double) << ' ' << sizeof(d) << '\n';
}


int main() {
    char c = 'a';
    int i = 0;
    int* p = &i;
    bool b = true;
    double d = 1.0;

    sizes(c, i, p, b, d);

    vector<int> v(1000);
    cout << "the size of vector<int>(1000) is "
         << sizeof(v) << '\n';
}
