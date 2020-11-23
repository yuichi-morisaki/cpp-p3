#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<bool> primality;
    for (int n = 0; n <= 100; ++n) {
        if (n < 2)
            primality.push_back(false);
        else
            primality.push_back(true);
    }

    for (int n = 0; n <= 100; ++n) {
        if (!primality[n])
            continue;
        cout << n << ' ';
        int a = 1;
        while (a * n <= 100) {
            primality[a * n] = false;
            ++a;
        }
    }
    cout << '\n';

    return 0;
}
