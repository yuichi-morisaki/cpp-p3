#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win9 {Point {100, 100}, 600, 400, "Lines"};

    Closed_polyline cpl = {
        {100, 100}, {150, 200}, {250, 250}, {300, 200}
    };
    win9.attach(cpl);
    cpl.add(Point {100, 250});

    Text t {Point {200, 200},
        "A closed polyline that isn't a polygon"};
    t.set_color(Color::blue);
    win9.attach(t);

    win9.wait_for_button();

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
