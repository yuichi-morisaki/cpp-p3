#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "marks"};

    Marks pp {"x", {
        Point {100, 100},
        Point {150, 200},
        Point {250, 250},
        Point {300, 200},
    }};

    win.attach(pp);

    return gui_main();
}
