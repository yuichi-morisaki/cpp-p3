#include <algorithm>
#include <initializer_list>
#include <iostream>
using namespace std;


class vector {
public:
    // constructors
    explicit vector(unsigned int s)
        : sz {s}, elem {new double[sz]}
    {
        for (int i = 0; i < s; ++i)
            elem[i] = 0;
    }

    // constructor with initializer list
    vector(initializer_list<double> lst)
        : sz {lst.size()}, elem {new double[sz]}
    {
        copy(lst.begin(), lst.end(), elem);
    }

    vector(const vector&);      // copy constructor
    vector(vector&&);           // move constructor

    // destructor
    ~vector() { delete[] elem; }

    // operators
    vector& operator=(const vector&);
    vector& operator=(vector&&);
    double& operator[](int n) { return elem[n]; }
    double operator[](int n) const { return elem[n]; }

    // other member functions
    int size() const { return sz; }

    double get(int n) const { return elem[n]; }
    void set(int n, double v) { elem[n] = v; }

private:
    unsigned int sz;
    double* elem;
};


vector::vector(const vector& v)
    : sz {v.sz}, elem {new double[v.sz]}
{
    copy(v.elem, &v.elem[v.sz], elem);
}

vector& vector::operator=(const vector& v) {
    double* p = new double[v.sz];
    copy(v.elem, &v.elem[v.sz], p);
    delete[] elem;
    elem = p;
    sz = v.sz;
    return *this;
}

vector::vector(vector&& v)
    : sz {v.sz}, elem {v.elem}
{
    v.sz = 0;
    v.elem = nullptr;
}

vector& vector::operator=(vector&& v) {
    delete[] elem;
    elem = v.elem;
    sz = v.sz;
    v.sz = 0;
    v.elem = nullptr;
    return *this;
}

// ----------------------------------------------------------------

void f(const vector& cv, vector& v) {
    double d = cv[1];
    cv[1] = 2.0;
    d = v[1];
    v[1] = 2.0;
}

int main() {
}
