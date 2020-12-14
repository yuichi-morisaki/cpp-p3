#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "color chart"};

    Vector_ref<Rectangle> vr;

    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16; ++j) {
            vr.push_back(
                    new Rectangle {Point {i*20, j*20}, 20, 20});
            Color col {static_cast<unsigned int>(i*16 + j)};
            vr[vr.size()-1].set_fill_color(col);
            win.attach(vr[vr.size()-1]);
        }

    return gui_main();
}
