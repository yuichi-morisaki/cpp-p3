#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "marked polyline"};

    Marked_polyline mpl {"1234"};

    mpl.add(Point {100, 100});
    mpl.add(Point {150, 200});
    mpl.add(Point {250, 250});
    mpl.add(Point {300, 200});

    win.attach(mpl);

    Marked_polyline mpl2 {"567", {
            Point {200, 100},
            Point {250, 200},
            Point {350, 250},
            Point {400, 200},
    }};
    win.attach(mpl2);

    return gui_main();
}
