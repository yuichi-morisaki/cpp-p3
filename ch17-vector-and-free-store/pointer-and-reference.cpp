#include <iostream>
using namespace std;

int main() {
    int x = 10;         int y = 10;
    cout << "x = " << x << "\t\ty = " << y << '\n';
    int* p = &x;        int& r = y;
    cout << "p = " << p << "\tr = " << r << '\n';
    *p = 7;             r = 7;
    cout << "x = " << x << "\t\ty = " << y << '\n';
    int x2 = *p;        int y2 = r;
    cout << "x2 = " << x2 << "\t\ty2 = " << y2 << '\n';
    int* p2 = &x2;      int& r2 = y2;
    cout << "p2 = " << p2 << "\tr2 = " << r2 << '\n';
    p2 = p;             r2 = r;
    cout << "p2 = " << p2 << "\tr2 = " << r2 << '\n';
    p = &x2;            // r = &y2; // error
    cout << "p = " << p << '\n';
}
