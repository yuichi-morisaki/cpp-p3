#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win15 {Point {100, 100}, 600, 400, "Lines"};

    Image rita {Point {0, 0}, "../fltk/rita.jpg"};
    Image path {Point {0, 0}, "../fltk/rita_path.gif"};
    path.set_mask(Point {50, 250}, 600, 400);

    win15.attach(path);
    win15.attach(rita);

    win15.wait_for_button();

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
