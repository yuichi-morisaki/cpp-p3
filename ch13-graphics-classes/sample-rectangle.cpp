#include "../fltk/Simple_window.h"
#include "../fltk/Graph.h"

using namespace Graph_lib;

int main()
try {
    Simple_window win7 {Point {100, 100}, 600, 400, "Lines"};

    Rectangle rect00 {Point {150, 100}, 200, 100};
    Rectangle rect11 {Point {50, 50}, Point {250, 150}};
    Rectangle rect12 {Point {50, 150}, Point {250, 250}};
    Rectangle rect21 {Point {250, 50}, 200, 100};
    Rectangle rect22 {Point {250, 150}, 200, 100};

    rect00.set_fill_color(Color::yellow);
    rect11.set_fill_color(Color::blue);
    rect12.set_fill_color(Color::red);
    rect21.set_fill_color(Color::green);

    win7.attach(rect00);
    win7.attach(rect11);
    win7.attach(rect12);
    win7.attach(rect21);
    win7.attach(rect22);

    rect11.move(400, 0);
    rect11.set_fill_color(Color::white);

    win7.put_on_top(rect00);

    rect00.set_color(Color::invisible);
    rect11.set_color(Color::invisible);
    rect12.set_color(Color::invisible);
    rect21.set_color(Color::invisible);
    rect22.set_color(Color::invisible);

    win7.wait_for_button();

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
