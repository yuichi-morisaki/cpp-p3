#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

double sqrt_det(double a, double b, double c)
{
    double det = b * b - 4 * a * c;
    if (det < 0)
        throw runtime_error("No real roots.");
    return sqrt(det);
}

int main()
try {
    cout << "Enter three numbers for a, b, and c: ";
    double a, b, c;
    cin >> a >> b >> c;

    if (!cin)
        throw runtime_error("Failed to read inputs");

    double D = sqrt_det(a, b, c);
    cout << "The roots are "
         << (-1 * b + D) / (2 * a)
         << " and "
         << (-1 * b - D) / (2 * a) << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Fatal: Unknown error occurred\n";
    return 2;
}
