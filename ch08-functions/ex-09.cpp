#include <iostream>
#include <vector>
using namespace std;

double compute_value(
    const vector<double>& price,
    const vector<double>& weight)
{
    if (price.size() != weight.size())
        throw runtime_error(
                "The vector arguments must have the same length");
    double sum = 0;
    for (int i = 0; i < price.size(); ++i) {
        sum += price[i] * weight[i];
    }
    return sum;
}

int main()
{
    vector<double> price = {100, 300, 200};
    vector<double> weight = {140.5, 50.2, 91.7};

    double value = compute_value(price, weight);

    cout << value << '\n';

    return 0;
}
