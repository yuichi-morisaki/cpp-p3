#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Please enter a floating-point value: ";
    double n;
    // int n;
    cin >> n;
    cout << "n == " << n
         << "\nn+1 == " << n+1
         << "\nthree times n == " << 3*n
         << "\ntwice n == " << n+n
         << "\nn squared == " << n*n
         << "\nhalf of n == " << n/2
         // << "\nremainder of n divided by 2 == " << n%2
         << "\nsquare root of n == " << sqrt(n)
         << "\n";

    return 0;
}
