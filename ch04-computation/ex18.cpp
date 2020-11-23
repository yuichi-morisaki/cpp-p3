#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    cout << "Please enter the values of 'a', 'b', and 'c' "
         << "in the equation 'a*x^2 + b*x + c = 0'\n";
    double a, b, c;
    cin >> a >> b >> c;

    double D = b * b - 4 * a * c;
    double x1 = (-1 * b + sqrt(D)) / (2 * a);
    double x2 = (-1 * b - sqrt(D)) / (2 * a);

    cout << "The solutions are "
         << x1 << " and " << x2 << '\n';

    return 0;
}
