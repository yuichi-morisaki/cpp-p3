#include <iostream>
#include <vector>
using namespace std;

struct X {
    int val;
    void out(const string&, int);

    X();
    X(int);
    X(const X&);
    X& operator=(const X&);
    ~X();
};

void X::out(const string& s, int nv) {
    cerr << '\t'
         << this << "->" << s << ":"
         << val << "(" << nv << ")\n";
}

X::X() {
    out("X()", 0);
    val = 0;
}

X::X(int v) {
    val = v;
    out("X(int)", v);
}

X::X(const X& x) {
    val = x.val;
    out("X(X&)", x.val);
}

X& X::operator=(const X& a) {
    out("X::operator=()", a.val);
    val = a.val;
    return *this;
}

X::~X() {
    out("~X()", 0);
}


X glob(2);      // a global variable

X copy(X a) {
    return a;
}

X copy2(X a) {
    X aa = a;
    return aa;
}

X copy3(X a) {
    X aa = a;
    X aaa = aa;
    return aaa;
}

X& ref_to(X& a) {
    return a;
}

X* make(int i) {
    X a(i);
    return new X(a);
}

struct XX {
    X a;
    X b;
};


int main() {
    cout << "X loc {4};\n";
    X loc {4};
    cout << "X loc2 {loc};\n";
    X loc2 {loc};
    cout << "loc = X {5};\n";
    loc = X {5};
    cout << "loc2 = copy(loc);\n";
    loc2 = copy(loc);
    cout << "loc2 = copy2(loc);\n";
    loc2 = copy2(loc);
    cout << "loc2 = copy3(loc);\n";
    loc2 = copy3(loc);
    cout << "X loc3 {6};\n";
    X loc3 {6};
    cout << "X& r = ref_to(loc);\n";
    X& r = ref_to(loc);
    cout << "delete make(7);\n";
    delete make(7);
    cout << "delete make(8);\n";
    delete make(8);
    cout << "vector<X> v(4);\n";
    vector<X> v(4);
    cout << "XX loc4;\n";
    XX loc4;
    cout << "X* p = new X {9};\n";
    X* p = new X {9};
    cout << "delete p;\n";
    delete p;
    cout << "X* pp = new X[5];\n";
    X* pp = new X[5];
    cout << "delete[] pp;\n";
    delete[] pp;
}
