#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win11 {Point {100, 100}, 600, 400, "Lines"};

    Ellipse e1 {Point {200, 200}, 50, 50};
    Ellipse e2 {Point {200, 200}, 100, 50};
    Ellipse e3 {Point {200, 200}, 100, 150};

    win11.attach(e1);
    win11.attach(e2);
    win11.attach(e3);

    win11.wait_for_button();

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
