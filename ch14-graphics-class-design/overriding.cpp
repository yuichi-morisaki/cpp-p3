#include <iostream>
using namespace std;

struct B {
    virtual void f() const {
        cout << "B::f ";
    }
    void g() const {
        cout << "B::g ";
    }
};

struct D : B {
    void f() const override {
        cout << "D::f ";
    }
    void g() {
        cout << "D::g ";
    }
};

struct DD : D {
    void f() {
        cout << "DD::f ";
    }
    void g() const {
        cout << "DD::g ";
    }
};

void call(const B& b) {
    b.f();
    b.g();
    cout << '\n';
}

int main() {
    B b;
    D d;
    DD dd;

    call(b);        // B::f B::g
    call(d);        // D::f B::g
    call(dd);       // D::f B::g

    b.f();          // B::f
    b.g();          // B::g
    cout << '\n';

    d.f();          // D::f
    d.g();          // D::g
    cout << '\n';

    dd.f();         // DD::f
    dd.g();         // DD::g
    cout << '\n';
}
