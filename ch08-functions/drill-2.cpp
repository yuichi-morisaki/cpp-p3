#include <iostream>
using namespace std;

void swap_v(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_r(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_cr(const int& a, const int& b)
{
    int temp;
    temp = a;
//    a = b;      // error: assignment of read-only reference
//    b = temp;   // error:
}

int main()
{
    int x = 7;
    int y = 9;

    cout << "Before 1: x = " << x << " and y = " << y << '\n';
    swap_v(x, y);
    cout << "After  1: x = " << x << " and y = " << y << '\n';
    cout << "Before 2: x = " << x << " and y = " << y << '\n';
    swap_r(x, y);
    cout << "After  2: x = " << x << " and y = " << y << '\n';
//    swap_cr(x, y);

    const int cx = 7;
    const int cy = 9;

    cout << "Before 4: cx = " << cx << " and cy = " << cy << '\n';
    swap_v(cx, cy);
    cout << "After  4: cx = " << cx << " and cy = " << cy << '\n';
//    swap_r(cx, cy);     // error: binding reference of type 'int&' to 'const int' discards qualifiers
//    swap_cr(cx, cy);

    swap_v(7.7, 9.9);
//    swap_r(7.7, 9.9);   // error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'
//    swap_cr(7.7, 9.9);

    double dx = 7.7;
    double dy = 9.9;

    swap_v(dx, dy);
//    swap_r(dx, dy);     // error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'
//    swap_cr(dx, dy);

    return 0;
}
