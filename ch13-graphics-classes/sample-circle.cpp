#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win10 {Point {100, 100}, 600, 400, "Lines"};

    Circle c1 {Point {100, 200}, 50};
    Circle c2 {Point {150, 200}, 100};
    Circle c3 {Point {200, 200}, 150};

    win10.attach(c1);
    win10.attach(c2);
    win10.attach(c3);

    win10.wait_for_button();

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
