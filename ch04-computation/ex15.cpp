#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int, vector<int>);

int main()
{
    cout << "How many prime numbers do you want? ";
    int n;
    cin >> n;

    vector<int> primes;
    int i = 2;
    while (n > 0) {
        if (is_prime(i, primes)) {
            primes.push_back(i);
            --n;
        }
        ++i;
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
