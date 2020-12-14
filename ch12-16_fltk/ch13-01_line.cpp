#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "two 'Line's"};

    Line horizontal {Point {100, 300}, Point {500, 300}};
    Line vertical {Point {100, 100}, Point {100, 300}};

    win.attach(horizontal);
    win.attach(vertical);

    return gui_main();
}
