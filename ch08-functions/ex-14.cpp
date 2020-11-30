#include <iostream>
using namespace std;

void f(const int x)
{
    cout << x << '\n';
}

/*
void g(const int x)
{
    ++x;    // error: read-only
    cout << x << '\n';
}
*/

int main()
{
    int x = 2;
    f(x);
//    g(x);

    return 0;
}
