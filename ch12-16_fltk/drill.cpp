#include "graph.h"
#include "window.h"
#include "image.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 1000, 800, "Drill in chapter 13"
    };

    Lines grid {};
    for (int x = 0; x <= 800; x += 100)
        grid.add(Point {x, 0}, Point {x, 800});
    for (int y = 0; y <= 800; y += 100)
        grid.add(Point {0, y}, Point {800, y});
    win.attach(grid);

    Vector_ref<Rectangle> vr;
    for (int i = 0; i < 8; ++i) {
        vr.push_back(
            new Rectangle {Point {i*100, i*100}, 100, 100});
        vr[vr.size() - 1].set_fill_color(Color::red);
        win.attach(vr[vr.size() - 1]);
    }

    Image rita_path1 {Point {400, 0}, "rita_path.gif"};
    Image rita_path2 {Point {600, 200}, "rita_path.gif"};
    Image rita_path3 {Point {100, 500}, "rita_path.gif"};
    rita_path1.set_mask(Point {0, 0}, 200, 200);
    rita_path2.set_mask(Point {200, 0}, 200, 200);
    rita_path3.set_mask(Point {0, 200}, 200, 200);
    win.attach(rita_path1);
    win.attach(rita_path2);
    win.attach(rita_path3);

    return gui_main();
}
