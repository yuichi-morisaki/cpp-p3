#include "window.h"
#include "graph.h"

namespace Graph_lib {

// ================================================================

Window::Window(Point p, int ww, int hh, const string& title)
    : Fl_Window {p.x, p.y, ww, hh, title.c_str()},
      w {ww},
      h {hh}
{
    init();
}


void Window::set_label(const string& s)
{
    copy_label(s.c_str());  // Fl_Window
}


int Window::x_max() const
{
    return w;
}


int Window::y_max() const
{
    return h;
}


void Window::attach(Shape& s)
{
    shapes.push_back(&s);
}


void Window::put_on_top(Shape& s)
{
    for (int i = 0; i < shapes.size(); ++i) {
        if (&s == shapes[i]) {
            if (i == shapes.size() - 1)
                return;
            for (++i; i < shapes.size(); ++i)
                shapes[i-1] = shapes[i];
            shapes[shapes.size() - 1] = &s;
            return;
        }
    }
}


void Window::init()
{
    resizable(this);    // Fl_Window
    show();             // Fl_Window
}


void Window::draw()
{
    Fl_Window::draw();
    for (int i = 0; i < shapes.size(); ++i)
        shapes[i]->draw();
}

// ================================================================

int gui_main()
{
    return Fl::run();
}

}   // END of ``namespace Graph_lib''
