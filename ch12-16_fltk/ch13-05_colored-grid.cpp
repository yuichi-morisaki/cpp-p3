#include "graph.h"
#include "window.h"

using namespace Graph_lib;

int main()
{
    Graph_lib::Window win {
        Point {100, 100}, 600, 400, "colored grid"};

    int x_size = win.x_max();
    int y_size = win.y_max();
    int x_grid = 80;
    int y_grid = 40;

    Lines grid;
    for (int x = x_grid; x < x_size; x += x_grid)
        grid.add(Point {x, 0}, Point {x, y_size});
    for (int y = y_grid; y < y_size; y += y_grid)
        grid.add(Point {0, y}, Point {x_size, y});

    grid.set_color(Color::red);

    win.attach(grid);

    return gui_main();
}
