#include <iostream>
using namespace std;

int main() {
    int* p1 = new int {77};
    int* q1 = p1;
    *p1 = 88;
    cout << *p1 << ' ' << *q1 << '\n';      // 88 88

    int* p2 = new int {77};
    int* q2 = new int {*p2};
    *p2 = 88;
    cout << *p2 << ' ' << *q2 << '\n';      // 88 77
}
