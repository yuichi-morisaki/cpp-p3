#include <algorithm>

using namespace std;

class vector {
public:
    vector() {}     // default constructor
    explicit vector(unsigned int);
    vector(const vector&);  // copy constructor
    vector(vector&&);       // move constructor
    ~vector();      // destructor

    vector& operator=(const vector&);
    vector& operator=(vector&&);
    double& operator[](unsigned int);
    const double& operator[](unsigned int) const;

    unsigned int capacity() const { return _space; };
    void push_back(double);
    void resize(unsigned int newsize);
    void reserve(unsigned int newalloc);

private:
    unsigned int _size {0};
    double* _elem {nullptr};
    unsigned int _space {0};
};


vector::vector(unsigned int s)
    : _size {s},
      _elem {new double[s]},
      _space {s}
{
    for (int i = 0; i < _size; ++i)
        _elem[i] = 0.0;
}

vector::vector(const vector& v)
    : _size {v._size},
      _elem {new double[v._size]},
      _space {v._size}
{
    copy(v._elem, &v._elem[v._size], _elem);
}

vector::vector(vector&& v)
    : _size {v._size},
      _elem {v._elem},
      _space {v._space}
{
    v._size = v._space = 0;
    v._elem = nullptr;
}

vector::~vector() {
    delete[] _elem;
}


void vector::push_back(double d) {
    if (_space == 0)
        reserve(8);
    else if (_size == _space)
        reserve(2 * _space);

    _elem[_size] = d;
    ++_size;
}

void vector::reserve(unsigned int newalloc) {
    if (newalloc <= _space) return;

    double* p = new double[newalloc];
    for (int i = 0; i < _size; ++i)
        p[i] = _elem[i];

    delete[] _elem;
    _elem = p;
    _space = newalloc;
}


vector& vector::operator=(const vector& v) {
    if (this == &v) return *this;

    if (v._size <= _space) {
        for (int i = 0; i < v._size; ++i)
            _elem[i] = v._elem[i];
        _size = v._size;
        return *this;
    }

    double* p = new double[v._size];
    for (int i = 0; i < v._size; ++i)
        p[i] = v._elem[i];
    delete[] _elem;
    _elem = p;
    _space = _size = v._size;
    return *this;
}

vector& vector::operator=(vector&& v) {
    delete[] _elem;
    _elem = v._elem;
    _size = v._size;
    _space = v._space;

    v._size = v._space = 0;
    v._elem = nullptr;

    return *this;
}

double& vector::operator[](unsigned int n) {
    return _elem[n];
}

const double& vector::operator[](unsigned int n) const {
    return _elem[n];
}


void vector::resize(unsigned int newsize) {
    reserve(newsize);
    for (int i = _size; i < newsize; ++i)
        _elem[i] = 0;
    _size = newsize;
}


int main() {
}
