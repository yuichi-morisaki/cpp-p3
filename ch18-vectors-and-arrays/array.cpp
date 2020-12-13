#include <iostream>
using namespace std;

const int MAX = 100;
int gai[MAX];       // a global array (of 100 ints)

void f(int n) {
    char lac[20];   // a local array
    int lai[60];
    double lad[n];  // error? : array size not a constant
}

void f2() {
    char lac[20];
    lac[7] = 'a';
    *lac = 'b';

    lac[-2] = 'b';
    lac[200] = 'c';
}

int main() {
    {
        double ad[10];
        for (int i = 0; i < 10; ++i) ad[i] = 0;
        double* p = &ad[5];
        *p = 7;
        p[2] = 6;
        p[-3] = 9;

        for (double* p = &ad[0]; p < &ad[10]; ++p)
            cout << *p << ' ';
        cout << '\n';
        for (double* p = &ad[9]; p >= &ad[0]; --p)
            cout << *p << ' ';
        cout << '\n';
    }

    char ch[100];
    cout << sizeof(ch) << '\n';

    char* p = ch;
    cout << sizeof(p) << ' ' << sizeof(&ch[0]) << '\n';
}
