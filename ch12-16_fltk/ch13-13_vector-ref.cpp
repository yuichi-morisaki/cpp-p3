#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "Vector_ref"};

    Vector_ref<Rectangle> rect;

    Rectangle x {Point {100, 200}, Point {200, 300}};
    rect.push_back(x);      // add named object

    rect.push_back(         // add unnamed object
        new Rectangle {Point {50, 60}, Point {80, 90}});

    for (int i = 0; i < rect.size(); ++i) {
        win.attach(rect[i]);
        rect[i].move(10, 10);
    }

    return gui_main();
}
