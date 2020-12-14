#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "one 'Lines'"};

    Lines x;
    x.add(Point {100, 300}, Point {500, 300});
    x.add(Point {100, 100}, Point {100, 300});

    win.attach(x);

    return gui_main();
}
