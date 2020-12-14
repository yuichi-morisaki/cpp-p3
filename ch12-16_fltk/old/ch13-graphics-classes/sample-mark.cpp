#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win14 {Point {100, 100}, 600, 400, "Lines"};

    Mark m1 {Point {100, 200}, 'x'};
    Mark m2 {Point {150, 200}, 'y'};
    Mark m3 {Point {200, 200}, 'z'};
    win14.attach(m1);
    win14.attach(m2);
    win14.attach(m3);

    Circle c1 {Point {100, 200}, 50};
    Circle c2 {Point {150, 200}, 100};
    Circle c3 {Point {200, 200}, 150};
    c1.set_color(Color::blue);
    c2.set_color(Color::red);
    c3.set_color(Color::green);
    win14.attach(c1);
    win14.attach(c2);
    win14.attach(c3);

    win14.wait_for_button();

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}
