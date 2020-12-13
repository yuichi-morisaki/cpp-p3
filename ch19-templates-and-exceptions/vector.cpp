
template<typename T>
class vector {
    T* elm {nullptr};
    int sz {0};
    int spc {0};
public:
    vector() {}
    explicit vector(int s);
    vector(const vector&);
    vector(vector&&);
    ~vector() { delete[] elm; }

    vector& operator=(const vector&);
    vector& operator=(vector&&);
    T& operator[](int n) { return elm[n]; }
    const T& operator[](int n) { return elm[n]; }

    int size() const { return sz; }
    int capacity() const { return spc; }

    void resize(int newsize);
    void push_back(const T& d);
    void reserve(int newalloc);
};
