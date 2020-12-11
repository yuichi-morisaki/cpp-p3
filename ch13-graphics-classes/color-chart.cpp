#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win8 {Point {100, 100}, 600, 400, "Lines"};

    Vector_ref<Rectangle> vr;
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16; ++j) {
            vr.push_back(
                    new Rectangle {Point {i*20, j*20}, 20, 20});
            vr[vr.size()-1].set_fill_color(Color {i*16+j});
            win8.attach(vr[vr.size()-1]);
        }

    win8.wait_for_button();

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}
