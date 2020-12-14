#ifndef WINDOW_GUARD
#define WINDOW_GUARD

#include "point.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Graph_lib {

class Shape;


class Window : public Fl_Window {
public:
    Window(Point xy, int w, int h, const string& title);

    void set_label(const string& label);
    int x_max() const;
    int y_max() const;

    void attach(Shape&);

    void put_on_top(Shape&);

private:
    vector<Shape*> shapes;
    int w;  // width
    int h;  // height

    void init();
    void draw();    // from protected
};

// ----------------------------------------------------------------

int gui_main();


}   // END of ``namespace Graph_lib''

#endif  // WINDOW_GUARD
