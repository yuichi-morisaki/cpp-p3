#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win2 {Point {100, 100}, 600, 400, "Lines"};

    Lines x;
    x.add(Point {100, 100}, Point {200, 100});
    x.add(Point {150, 50}, Point {150, 150});

    win2.attach(x);

    win2.wait_for_button();

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
