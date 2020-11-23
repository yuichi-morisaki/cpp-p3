#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int, vector<int>);

int main()
{
    vector<int> primes;

    cout << "Please enter a number to which"
         << " this program search for prime numbers: ";
    int max_n;
    cin >> max_n;
    for (int n = 1; n <= max_n; ++n) {
        if (is_prime(n, primes))
            primes.push_back(n);
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
