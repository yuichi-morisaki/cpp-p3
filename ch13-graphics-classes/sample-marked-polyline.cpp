#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win12 {Point {100, 100}, 600, 400, "Lines"};

    Marked_polyline mpl {"1234"};
    mpl.add(Point {100, 100});
    mpl.add(Point {150, 200});
    mpl.add(Point {250, 250});
    mpl.add(Point {300, 200});

    win12.attach(mpl);

    win12.wait_for_button();

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
