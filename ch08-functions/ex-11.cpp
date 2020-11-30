#include <iostream>
#include <vector>
using namespace std;

class Result {
    public:
        double smallest;
        double largest;
        double mean;
        double median;
        Result(double s, double l, double ma, double md)
            : smallest {s}, largest {l}, mean {ma}, median {md} { }
};

Result compute(const vector<double>& vec)
{
    if (vec.size() == 0)
        throw runtime_error("Empty vector");

    double smallest = vec[0];
    double largest = vec[0];
    double sum = 0;
    vector<double> copy_vec;

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] < smallest) smallest = vec[i];
        if (vec[i] > largest) largest = vec[i];
        sum += vec[i];
        copy_vec.push_back(vec[i]);
    }

    double mean = sum / vec.size();
    double median = (vec.size() % 2 == 0) ?
        (vec[vec.size() / 2 - 1] + vec[vec.size() / 2]) / 2 :
        vec[vec.size() / 2];

    return Result(smallest, largest, mean, median);
}

int main()
{
    vector<double> v2 = {4.8, 3.4, 2.3, 1.5};
    vector<double> v1 = {1.4, 2.6, 3.7, 4.2, 5.9};
    vector<double> v0;

    Result r2 = compute(v2);
    cout << "smallest: " << r2.smallest << '\n'
         << "largest : " << r2.largest << '\n'
         << "mean    : " << r2.mean << '\n'
         << "median  : " << r2.median << '\n'
         << '\n';

    Result r1 = compute(v1);
    cout << "smallest: " << r1.smallest << '\n'
         << "largest : " << r1.largest << '\n'
         << "mean    : " << r1.mean << '\n'
         << "median  : " << r1.median << '\n'
         << '\n';

    Result r = compute(v0);

    return 0;
}
