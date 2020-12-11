#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    constexpr Point x {100, 100};
    Simple_window win1 {x, 600, 400, "two lines"};

    Line horizontal {x, Point {200, 100}};
    Line vertical {Point {150, 50}, Point {150, 150}};

    win1.attach(horizontal);
    win1.attach(vertical);

    win1.wait_for_button();

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
