#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "different colored lines"};

    Line horizontal {Point {100, 300}, {500, 300}};
    Line vertical {Point {100, 100}, {100, 300}};

    horizontal.set_color(Color::red);
    vertical.set_color(Color::dark_green);

    win.attach(horizontal);
    win.attach(vertical);

    return gui_main();
}
