#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1 = {5, 7, 9, 4, 6, 8};
    for (int i = 0; i < v1.size(); ++i)
        cout << v1[i] << '\n';

    vector<string> v2(6);
    for (int j = 0; j < v2.size(); ++j) 
        cout << j << "\t'" << v2[j] << "'\n";

    vector<double> v3;
    v3.push_back(2.7);
    v3.push_back(5.6);
    v3.push_back(7.9);

    for (double x: v3)
        cout << x << '\n';

    return 0;
}
