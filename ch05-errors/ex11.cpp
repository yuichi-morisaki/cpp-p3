#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

vector<int> fib_nums;

int fib(int n)
{
    if (n < fib_nums.size())
        return fib_nums[n];

    int fib_prev_2 = fib(n - 2);
    int fib_prev = fib(n - 1);
    if (fib_prev > numeric_limits<int>::max() - fib_prev_2)
        throw runtime_error("Exceed the limit of max of int");
    int result = fib_prev_2 + fib_prev;
    fib_nums.push_back(result);
    return result;
}

int main()
try {
    // initialize the vector
    fib_nums.push_back(1);  // n == 0
    fib_nums.push_back(1);  // n == 1

    for (int i = 0; ; ++i)
        cout << i << '\t' << fib(i) << '\n';

    return 0;
}
catch (exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Fatal: Unknown error occurred.\n";
    return 2;
}
