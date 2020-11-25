#include <iostream>
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
        throw runtime_error(
                "Invalid input for N: non-positive integer");

    cout << "Please enter some numbers (press '|' to stop):\n";
    vector<double> numbers;
    for (double d; cin >> d; )
        numbers.push_back(d);

    if (N > numbers.size())
        throw runtime_error(
                "You want a sum of more numbers than you input!");

    double sum = 0;
    for (int i = 0; i < N; ++i)
        sum += numbers[i];
    
    cout << "The sum of the first " << N << " numbers ( ";
    for (int i = 0; i < N; ++i)
        cout << numbers[i] << ' ';
    cout << ") is " << sum << '\n';

    vector<double> diffs;
    double prev = numbers[0];
    for (int i = 1; i < N; ++i) {
        double curr = numbers[i];
        double diff = prev - curr;
        diffs.push_back(diff);
        prev = curr;
    }
    for (double d: diffs)
        cout << d << ' ';
    cout << '\n';

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
