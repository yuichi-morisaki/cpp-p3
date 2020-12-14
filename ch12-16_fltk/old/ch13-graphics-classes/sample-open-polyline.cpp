#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win4 {Point {100, 100}, 600, 400, "Lines"};

    Open_polyline opl = {
        {100, 100}, {150, 200}, {250, 250}, {300, 200}
    };

    win4.attach(opl);

    win4.wait_for_button();

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
