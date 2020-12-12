class B {
public:
    virtual void f() = 0;
    virtual void g() = 0;
};

class D1 : public B {
public:
    void f() override {}
    void g() override {}
};

class D2 : public B {
public:
    void f() override {}
};

class D3 : public D2 {
public:
    void g() override {}
};

int main() {
    // B b;     // error: B is abstract
    D1 d1;
    // D2 d2;   // error: D2 is still abstract
    D3 d3;
}
