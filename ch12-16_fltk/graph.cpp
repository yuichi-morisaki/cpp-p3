#include "graph.h"

#include <cmath>
#include <stdexcept>

using std::runtime_error;

namespace Graph_lib {

// ================================================================

Color::Color(Color_type cc)
    : c {cc},
      v {Color::visible}
{
}


Color::Color(Color_type cc, Transparency vv)
    : c {cc},
      v {vv}
{
}


Color::Color(unsigned int col)
    : c {Fl_Color {col}},
      v {Color::visible}
{
}


Color::Color(Transparency vv)
    : c {Fl_Color {}},
      v {vv}
{
}


int Color::as_int() const
{
    return c;
}


unsigned char Color::visibility() const
{
    return v;
}


void Color::set_visibility(Transparency vv)
{
    v = vv;
}

// ----------------------------------------------------------------

Line_style::Line_style(Line_style_type ss)
    : s {ss},
      w {0}
{
}


Line_style::Line_style(Line_style_type ss, int ww)
    : s {ss},
      w {ww}
{
}


Line_style::Line_style(int line_style)
    : s {line_style},
      w {0}
{
}


int Line_style::width() const
{
    return w;
}


int Line_style::style() const
{
    return s;
}

// ----------------------------------------------------------------

Font::Font(Font_type ff)
    : f {ff}
{
}


Font::Font(int ff)
    : f {ff}
{
}


int Font::as_int() const
{
    return f;
}

// ================================================================

Shape::Shape(initializer_list<Point> lst)
{
    for (Point p: lst)
        add(p);
}


void Shape::draw() const
{
    Fl_Color oldc = fl_color();     // save current color
        // no good way for retrieving current style

    fl_color(lcolor.as_int());
    fl_line_style(ls.style(), ls.width());

    draw_lines();

    fl_color(oldc);     // restore
    fl_line_style(0);   // default
}


void Shape::draw_lines() const
{
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for (int i = 0; i < number_of_points(); ++i)
            fl_vertex(point(i).x, point(i).y);
        fl_end_complex_polygon();
        fl_color(color().as_int());
    }

    if (color().visibility() && 1 < number_of_points())
        for (int i = 1; i < number_of_points(); ++i)
            fl_line(points[i-1].x,
                    points[i-1].y,
                    points[i].x,
                    points[i].y);
}


void Shape::move(int dx, int dy)
{
    for (int i = 0; i < points.size(); ++i) {
        points[i].x += dx;
        points[i].y += dy;
    }
}


void Shape::add(Point p)
{
    points.push_back(p);
}


void Shape::set_point(int i, Point p)
{
    points[i] = p;
}


int Shape::number_of_points() const
{
    return points.size();
}


Point Shape::point(int i) const
{
    return points[i];
}


Color Shape::color() const
{
    return lcolor;
}


Line_style Shape::style() const
{
    return ls;
}


Color Shape::fill_color() const
{
    return fcolor;
}


void Shape::set_color(Color col)
{
    lcolor = col;
}


void Shape::set_style(Line_style sty)
{
    ls = sty;
}


void Shape::set_fill_color(Color col)
{
    fcolor = col;
}

// ================================================================

Line::Line(Point p1, Point p2)
{
    add(p1);
    add(p2);
}

// ----------------------------------------------------------------

Lines::Lines()
{
}


Lines::Lines(initializer_list<pair<Point, Point>> lst)
{
    for (auto p: lst)
        add(p.first, p.second);
}


void Lines::add(Point p1, Point p2)
{
    Shape::add(p1);
    Shape::add(p2);
}


void Lines::draw_lines() const
{
    if (color().visibility())
        for (int i = 1; i < number_of_points(); i += 2)
            fl_line(point(i-1).x,
                    point(i-1).y,
                    point(i).x,
                    point(i).y);
}

// ----------------------------------------------------------------

Open_polyline::Open_polyline()
{
}


Open_polyline::Open_polyline(initializer_list<Point> lst)
    : Shape {lst}
{
}


void Open_polyline::add(Point p)
{
    Shape::add(p);
}

// ----------------------------------------------------------------

void Closed_polyline::draw_lines() const
{
    Open_polyline::draw_lines();

    if (2 < number_of_points() && color().visibility())
        fl_line(point(number_of_points()-1).x,
                point(number_of_points()-1).y,
                point(0).x,
                point(0).y);
}

// ----------------------------------------------------------------

Polygon::Polygon()
{
}


Polygon::Polygon(initializer_list<Point> lst)
{
    for (Point p: lst)
        add(p);
}


pair<double, double>
line_intersect(
    Point p1, Point p2, Point p3, Point p4, bool& parallel)
{
    double x1 = p1.x;   double y1 = p1.y;
    double x2 = p2.x;   double y2 = p2.y;
    double x3 = p3.x;   double y3 = p3.y;
    double x4 = p4.x;   double y4 = p4.y;

    double denom = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    if (denom == 0) {
        parallel = true;
        return pair<double, double>(0, 0);
    }
    parallel = false;
    return pair<double, double>(
        ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom,
        ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom);
}

bool line_segment_intersect(
    Point p1, Point p2, Point p3, Point p4, Point& intersection)
{
    bool parallel;
    pair<double, double> u
            = line_intersect(p1, p2, p3, p4, parallel);
    if (parallel
            || u.first < 0 || 1 < u.first
            || u.second < 0 || 1 < u.second)
        return false;

    intersection.x = p1.x + u.first * (p2.x - p1.x);
    intersection.y = p1.y + u.first * (p2.y - p1.y);
    return true;
}

void Polygon::add(Point p)
{
    // check that new line doesn't intersect existing lines
    int np = number_of_points();
    if (np > 1) {
        if (p == point(np-1))
            throw runtime_error(
                    "polygon point equal to previous point");
        bool parallel;
        line_intersect(
                point(np-1), p, point(np-2), point(np-1),
                parallel);
        if (parallel)
            throw runtime_error(
                    "two polygon points lie in a straight line");
    }
    for (int i = 1; i < np-1; ++i) {
        Point ignore {0, 0};
        if (line_segment_intersect(
                    point(np-1), p, point(i-1), point(i),
                    ignore))
            throw runtime_error(
                    "intersect in polygon");
    }

    Closed_polyline::add(p);
}

// ----------------------------------------------------------------

Rectangle::Rectangle(Point tl, int ww, int hh)
    : w {ww},
      h {hh}
{
    if (h <= 0 || w <= 0)
        throw runtime_error("Bad rectangle: non-positive side");
    add(tl);
}


Rectangle::Rectangle(Point tl, Point br)
    : w {br.x - tl.x},
      h {br.y - tl.y}
{
    if (h <= 0 || w <= 0)
        throw runtime_error(
                "Bad rectangle: first point is not top left");
    add(tl);
}


int Rectangle::height() const
{
    return h;
}


int Rectangle::width() const
{
    return w;
}


void Rectangle::draw_lines() const
{
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x, point(0).y, w, h);
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_rect(point(0).x, point(0).y, w, h);
    }
}

// ----------------------------------------------------------------

Text::Text(Point p, const string& s)
    : lab {s}
{
    add(p);
}


void Text::draw_lines() const
{
    int old_fnt = fl_font();
    int old_sz = fl_size();

    fl_font(fnt.as_int(), fnt_sz);
    fl_draw(lab.c_str(), point(0).x, point(0).y);

    fl_font(old_fnt, old_sz);
}


void Text::set_label(const string& s)
{
    lab = s;
}


void Text::set_font(Font f)
{
    fnt = f;
}


void Text::set_font_size(int sz)
{
    fnt_sz = sz;
}


string Text::label() const
{
    return lab;
}


Font Text::font() const
{
    return fnt;
}


int Text::font_size() const
{
    return fnt_sz;
}

// ----------------------------------------------------------------

Circle::Circle(Point p, int rr)
    : r {rr}
{
    add(Point {p.x - r, p.y - r});  // top left corner
}


void Circle::draw_lines() const
{
    if (color().visibility())
        fl_arc(point(0).x, point(0).y,      // top left corner
               r + r, r + r,            // width and height
               0, 360);         // beginning and end angle
}


Point Circle::center() const
{
    return Point {point(0).x + r,
                  point(0).y + r};
}


int Circle::radius() const
{
    return r;
}


void Circle::set_radius(int rr)
{
    set_point(0,
              Point {center().x - rr,
                     center().y - rr});
    r = rr;
}

// ----------------------------------------------------------------

Ellipse::Ellipse(Point p, int ww, int hh)
    : w {ww},
      h {hh}
{
    add(Point {p.x - ww, p.y - hh});
}


void Ellipse::draw_lines() const
{
    if (color().visibility())
        fl_arc(
            point(0).x, point(0).y,         // top left corner
            w + w, h + h,   // width and height
            0, 360);            // beginning and end angle
}


Point Ellipse::center() const
{
    return Point {point(0).x + w,
                  point(0).y + h};
}


Point Ellipse::focus_p() const
{
    if (h <= w)
        return Point {
            center().x + int(sqrt(double(w*w - h*h))),
            center().y
        };
    else
        return Point {
            center().x,
            center().y + int(sqrt(double(h*h - w*w)))
        };
}


Point Ellipse::focus_m() const
{
    if (h <= w)
        return Point {
            center().x - int(sqrt(double(w*w - h*h))),
            center().y
        };
    else
        return Point {
            center().x,
            center().y - int(sqrt(double(h*h - w*w)))
        };
}


void Ellipse::set_x_radius(int ww)
{
    set_point(0,
              Point {center().x - ww,
                     center().y - h});
    w = ww;
}


void Ellipse::set_y_radius(int hh)
{
    set_point(0,
              Point {center().x - w,
                     center().y - hh});
    h = hh;
}


int Ellipse::x_radius() const
{
    return w;
}


int Ellipse::y_radius() const
{
    return h;
}

// ----------------------------------------------------------------

Marked_polyline::Marked_polyline(const string& m)
    : mark {m}
{
    if (m == "")
        mark = "*";
}


Marked_polyline::Marked_polyline(const string& m,
                                 initializer_list<Point> lst)
    : Open_polyline {lst},
      mark {m}
{
    if (m == "")
        mark = "*";
}


void draw_mark(Point p, char c)
{
    constexpr int dx = 4;
    constexpr int dy = 4;

    string m(1, c);
    fl_draw(m.c_str(), p.x - dx, p.y - dy);
}

void Marked_polyline::draw_lines() const
{
    Open_polyline::draw_lines();

    for (int i = 0; i < number_of_points(); ++i)
        draw_mark(point(i), mark[i % mark.size()]);
}

// ---------------------------------------------------------------

Marks::Marks(const string& m)
    : Marked_polyline {m}
{
    set_color(Color {Color::invisible});
}


Marks::Marks(const string& m, initializer_list<Point> lst)
    : Marked_polyline {m, lst}
{
    set_color(Color {Color::invisible});
}

// ----------------------------------------------------------------

Mark::Mark(Point p, char c)
    : Marks {string(1, c)}
{
    add(p);
}

// ----------------------------------------------------------------

// ================================================================

}   // END of ``namespace Graph_lib''
