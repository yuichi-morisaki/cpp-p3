#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int, vector<int>);

int main()
{
    vector<int> primes;

    for (int n = 1; n <= 100; ++n) {
        cout << n;
        bool primality = is_prime(n, primes);
        if (primality) {
            primes.push_back(n);
            cout << " is prime.";
        }
        cout << '\n';
    }

    for (int p: primes)
        cout << p << ' ';
    cout << '\n';

    return 0;
}

bool is_prime(int n, vector<int> primes)
{
    if (n < 2)
        return false;

    for (int p: primes) {
        if (p >= n)
            break;
        if (n % p == 0)
            return false;
    }
    return true;
}
