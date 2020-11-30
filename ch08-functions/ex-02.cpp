#include <iostream>
#include <vector>
using namespace std;

void print(string label, vector<int>& vi)
{
    cout << label << '\n';
    for (int i: vi)
        cout << i << ' ';
    cout << '\n';
}

int main()
{
    string label = "Do you know 'pi?'";
    vector<int> vi = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    print(label, vi);

    return 0;
}
