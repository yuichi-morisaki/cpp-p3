#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout << "Please enter a number to which "
         << "this program search for prime numbers: ";
    int max_n;
    cin >> max_n;

    vector<bool> primality;
    for (int n = 0; n <= max_n; ++n) {
        if (n < 2)
            primality.push_back(false);
        else
            primality.push_back(true);
    }

    for (int n = 0; n <= max_n; ++n) {
        if (!primality[n])
            continue;
        cout << n << ' ';
        int a = 1;
        while (a * n <= max_n) {
            primality[a * n] = false;
            ++a;
        }
    }
    cout << '\n';

    return 0;
}
