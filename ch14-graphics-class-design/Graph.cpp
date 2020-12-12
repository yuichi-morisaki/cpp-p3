#include "Graph.h"

namespace Graph_lib {
    // ------------------------------------------------------------
    //  Line style

    Line_style::Line_style(Line_style_type lst)
        : s {lst}, w {0} {
    }


    Line_style::Line_style(Line_style_type lst, int ww)
        : s {lst}, w {ww} {
    }


    Line_style::Line_style(int ss)
        : s {ss}, w {0} {
    }


    int Line_style::width() const {
        return w;
    }


    int Line_style::style() const {
        return s;
    }

    // ------------------------------------------------------------
    //  Color

    Color::Color(Color_type cc)
        : c {Fl_Color {cc}}, v(visible) {
    }


    Color::Color(Color_type cc, Transparency vv)
        : c {Fl_Color {cc}}, v(vv) {
    }


    Color::Color(int cc)
        : c {Fl_Color(cc)}, v(visible) {
    }


    Color::Color(Transparency vv)
        : c {Fl_Color()}, v(vv) {
    }


    int Color::as_int() const {
        return c;
    }


    char Color::visibility() const {
        return v;
    }


    void Color::set_visibility(Transparency vv) {
        v = vv;
    }

    // ============================================================
    //  Shape @public

    void Shape::draw() const {
        Fl_Color oldc = fl_color();

        fl_color(lcolor.as_int());
        fl_line_style(ls.style(), ls.width());
        draw_lines();

        fl_color(oldc);
        fl_line_style(0);
    }


    void Shape::move(int dx, int dy) {
        for (int i = 0; i < points.size(); ++i) {
            points[i].x += dx;
            points[i].y += dy;
        }
    }


    void Shape::set_style(Line_style sty) {
        ls = sty;
    }

    Line_style Shape::style() const {
        return ls;
    }


    void Shape::set_color(Color col) {
        lcolor = col;
    }

    Color Shape::color() const {
        return lcolor;
    }


    void Shape::set_fill_color(Color col) {
        fcolor = col;
    }

    Color Shape::fill_color() const {
        return fcolor;
    }


    Point Shape::point(int nth) const {
        return points[nth];
    }

    int Shape::number_of_points() const {
        return points.size();
    }

    // ------------------------------------------------------------
    //  Shape @protected

    Shape::Shape(initializer_list<Point> lst) {
        for (Point p: lst)
            add(p);
    }


    void Shape::add(Point p) {
        points.push_back(p);
    }

    void Shape::set_point(int nth, Point p) {
        points[nth] = p;
    }

    // ============================================================

    Line::Line(Point p1, Point p2) {
        add(p1);
        add(p2);
    }


    Lines::Lines() {
    }


    Lines::Lines(initializer_list<pair<Point, Point>> lst) {
        for (auto p: lst)
            add(p.first, p.second);
    }


    void Lines::add(Point p1, Point p2) {
        Shape::add(p1);
        Shape::add(p2);
    }

    void Lines::draw_lines() const {
        if (color().visibility())
            for (int i = 1; i < number_of_points(); i += 2)
                fl_line(point(i-1).x,
                        point(i-1).y,
                        point(i).x,
                        point(i).y);
    }

    // ------------------------------------------------------------
    // ------------------------------------------------------------

}   // End of namespace Graph_lib
