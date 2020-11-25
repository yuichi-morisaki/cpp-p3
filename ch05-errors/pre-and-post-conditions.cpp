#include <iostream>

using namespace std;

int area(int length, int width)
{
    if (length <= 0 || width <= 0)
        throw runtime_error("area() pre-condition");
    int a = length * width;
    if (a <= 0)
        throw runtime_error("area() post-condition");
    return a;
}

int main()
{
    int len = 50000;
    int wid = 50000;

    int a = area(len, wid);     // runtime error for post condition

    cout << a << '\n';

    return 0;
}
