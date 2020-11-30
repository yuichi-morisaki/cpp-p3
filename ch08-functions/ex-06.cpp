#include <iostream>
#include <vector>
using namespace std;

vector<string>
reverse(const vector<string>& v)
{
    vector<string> res;
    for (int i = v.size() - 1; i >= 0; --i)
        res.push_back(v[i]);
    return res;
}

void swap(string& a, string& b)
{
    string temp = a;
    a = b;
    b = temp;
}

void inplace_reverse(vector<string>& v)
{
    for (int b = 0, e = v.size() -1; b < e; ++b, --e)
        swap(v[b], v[e]);
}

void print(vector<string>& v)
{
    for (string s: v)
        cout << s << ' ';
    cout << '\n';
}

int main()
{
    vector<string> v = {"foo", "bar", "baz", "hello", "bye"};
    print(v);
    vector<string> r = reverse(v);
    print(r);
    inplace_reverse(v);
    print(v);

    return 0;
}
