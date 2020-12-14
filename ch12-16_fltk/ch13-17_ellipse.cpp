#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "ellipse"};

    Ellipse e1 {Point {200, 200}, 50, 50};
    Ellipse e2 {Point {200, 200}, 100, 50};
    Ellipse e3 {Point {200, 200}, 100, 150};

    win.attach(e1);
    win.attach(e2);
    win.attach(e3);

    return gui_main();
}
