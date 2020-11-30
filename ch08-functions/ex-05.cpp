#include <iostream>
#include <vector>
using namespace std;

vector<int> reverse(const vector<int>& v)
{
    vector<int> res;
    for (int i = v.size() - 1; i >= 0; --i)
        res.push_back(v[i]);
    return res;
}

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void inplace_reverse(vector<int>& v)
{
    for (int b = 0, e = v.size() - 1; b < e; ++b, --e)
        swap(v[b], v[e]);
}

void print(vector<int>& v)
{
    for (int i: v)
        cout << i << ' ';
    cout << '\n';
}

int main()
{
    vector<int> v1 = {1, 3, 5, 7, 9};
    vector<int> v2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector<int> r1 = reverse(v1);
    vector<int> r2 = reverse(v2);
    print(v1);
    print(r1);
    print(v2);
    print(r2);

    inplace_reverse(v1);
    inplace_reverse(v2);
    print(v1);
    print(v2);

    return 0;
}
