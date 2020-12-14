#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "three circles"};

    Circle c1 {Point {100, 200}, 50};
    Circle c2 {Point {150, 200}, 100};
    Circle c3 {Point {200, 200}, 150};

    win.attach(c1);
    win.attach(c2);
    win.attach(c3);

    return gui_main();
}
