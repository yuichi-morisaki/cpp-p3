// -lfltk_images is required when linking

#include "graph.h"
#include "window.h"
#include "image.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "image"};

    Image rita {Point {0, 0}, "rita.jpg"};
    Image path {Point {0, 0}, "rita_path.gif"};
    path.set_mask(Point {50, 250}, 600, 400);

    win.attach(path);
    win.attach(rita);

    return gui_main();
}
