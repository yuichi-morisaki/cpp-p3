template<class T> class Vector_ref {
    public:
        // ...
        void push_back(T&);     // add a named object
        void push_back(T*);     // add an unnamed object

        T& operator[](int i);   // subscripting: read and write access
        const T& operator[](int i) const;

        int size() const;

    private:
};

void HOW_TO_USE_Vector_ref()
{
    Vector_ref<Rectangle> rect;

    Rectangle x {Point {100, 200}, Point {200, 300}};
    rect.push_back(x);

    rect.push_back(new Rectangle {Point {50, 60}, Point {80, 90}});

    for (int i = 0; i < rect.size(); ++i)
        rect[i].move(10, 10);
}
