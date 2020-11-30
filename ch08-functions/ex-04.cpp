#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void print(string label, vector<int>& vi)
{
    cout << label << '\n';
    for (int i = 0; i < vi.size(); ++i)
        cout << i << '\t' << vi[i] << '\n';
}

void fibonacci(int x, int y, vector<int>& v, int n)
{
    if (v.size() > 0)
        throw runtime_error("vector must be empty");
    v.push_back(x);
    v.push_back(y);
    int small = x;
    int large = y;
    while (v.size() < n) {
        int new_value = small + large;
        v.push_back(new_value);
        small = large;
        large = new_value;
        if (small > large)
            break;
    }
}

int main()
{
    string label = "Fibonacci sequence";
    vector<int> fib;

    int n;
    cin >> n;
    fibonacci(0, 1, fib, n);

    print(label, fib);

    return 0;
}
