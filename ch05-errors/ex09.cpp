#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
try {
    cout << "Please enter the number of values you want to sum: ";
    int N;
    cin >> N;
    if (!cin)
        throw runtime_error("Failed to read input for 'N'");
    if (N <= 0)
        throw runtime_error("Invalid input: non-positive integer");

    cout << "Please enter some integers (press '|' to stop): ";
    vector<int> numbers;
    for (int n; cin >> n; )
        numbers.push_back(n);

    if (N > numbers.size()) {
        cout << "You want a sum of more numbers than you input!\n";
    }
    else {
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            int n = numbers[i];
            if (n >= 0 && sum > numeric_limits<int>::max() - n)
                throw runtime_error("Exceed the max of integer");
            if (n < 0 && sum < numeric_limits<int>::min() - n)
                throw runtime_error("Exceed the min of integer");
            sum += n;
        }
        cout << "The sum of the first " << N << " numbers ( ";
        for (int i = 0; i < N; ++i)
            cout << numbers[i] << ' ';
        cout << ") is " << sum << '\n';
    }

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
