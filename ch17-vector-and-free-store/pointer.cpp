#include <iostream>
using namespace std;

int main() {
    int i = 17;
    int* pi = &i;

    double e = 2.71828;
    double* pd = &e;

    cout << "pi == " << pi
         << "; contents of pi == " << *pi << '\n';
    cout << "pd == " << pd
         << "; contents of pd == " << *pd << '\n';

    *pi = 27;
    *pd = 3.14159;

    cout << "pi == " << pi
         << "; contents of pi == " << *pi << '\n';
    cout << "pd == " << pd
         << "; contents of pd == " << *pd << '\n';

    *pd = *pi;

/* error: invalid conversions
    i = pi;
    pi = 7;

    char* pc = pi;
    pi = pc;
*/

    char ch1 = 'a';
    char ch2 = 'b';
    char ch3 = 'c';
    char ch4 = 'd';
    pi = &ch3;
}
