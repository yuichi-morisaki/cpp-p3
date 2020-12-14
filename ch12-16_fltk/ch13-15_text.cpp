#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "text with polyline"};

    Closed_polyline cpl {
        Point {100, 100},
        Point {150, 200},
        Point {250, 250},
        Point {300, 200},
    };
    cpl.add(Point {100, 250});
    win.attach(cpl);

    Text t {Point {200, 200}, "A closed polyline that isn't polygon"};
    t.set_color(Color::blue);
    win.attach(t);

    return gui_main();
}
