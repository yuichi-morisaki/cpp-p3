#include <iostream>
using namespace std;

double* calc(int res_size, int max) {
    double* p = new double[max];
    double* res = new double[res_size];

    // use p to calculate results to be put in res

    delete[] p;
    return res;
}

int main() {
    double* p = new double[4];
    *p = 7.7;
    p[2] = 9.9;

    double x = *p;
    double y = p[2];

    cout << "p[0] == " << x << '\n'
         << "p[2] == " << y << '\n';

    double* p2 = new double {5.5};

    double* p4 = new double[5] {0, 1, 2, 3, 4};

    double* p0 = nullptr;
    if (p0 != nullptr)
        cout << "p0 is not a nullptr\n";
    else
        cout << "p0 is a nullptr\n";

    if (p0)
        cout << "p0 is not a nullptr\n";
    else
        cout << "p0 is a nullptr\n";

    double* r = calc(100, 1000);
    // use r
    delete[] r;
}
