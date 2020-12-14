#ifndef GRAPH_GUARD
#define GRAPH_GUARD

#include "point.h"

#include <FL/fl_draw.H>

#include <initializer_list>
#include <string>
#include <vector>

using std::initializer_list;
using std::pair;
using std::string;
using std::vector;

namespace Graph_lib {

// ----------------------------------------------------------------

template<typename T>
class Vector_ref {
public:
    Vector_ref() {};

    ~Vector_ref() {
        for (int i = 0; i < owned.size(); ++i)
            delete owned[i];
    };

    void push_back(T& s) { v.push_back(&s); }

    void push_back(T* p) {
        v.push_back(p);
        owned.push_back(p);
    }

    T& operator[](int i) { return *v[i]; }

    const T& operator[](int i) const { return *v[i]; }

    int size() const { return v.size(); }

private:
    vector<T*> v;
    vector<T*> owned;
};

// ================================================================

struct Color {
    enum Color_type {
        white = FL_WHITE,
        black = FL_BLACK,
        red = FL_RED,           dark_red = FL_DARK_RED,
        green = FL_GREEN,       dark_green = FL_DARK_GREEN,
        blue = FL_BLUE,         dark_blue = FL_DARK_BLUE,
        yellow = FL_YELLOW,     dark_yellow = FL_DARK_YELLOW,
        magenta = FL_MAGENTA,   dark_magenta = FL_DARK_MAGENTA,
        cyan = FL_CYAN,         dark_cyan = FL_DARK_CYAN,
    };

    enum Transparency : unsigned char {
        invisible = 0,
        visible = 255,
    };

    Color(Color_type);
    Color(Color_type, Transparency);
    Color(unsigned int color);
    Color(Transparency);

    int as_int() const; 

    unsigned char visibility() const;
    void set_visibility(Transparency);

private:
    Fl_Color c;
    unsigned char v;     // visibility
};

// ----------------------------------------------------------------

struct Line_style {
    enum Line_style_type {
        solid = FL_SOLID,
        dash = FL_DASH,
        dot = FL_DOT,
        dashdot = FL_DASHDOT,
        dashdotdot = FL_DASHDOTDOT,
    };

    Line_style(Line_style_type);
    Line_style(Line_style_type, int line_width);
    Line_style(int line_style);

    int width() const;
    int style() const;

private:
    int s;  // style
    int w;  // width
};

// ----------------------------------------------------------------

struct Font {
    enum Font_type {
        helvetica = FL_HELVETICA,
        helvetica_bold = FL_HELVETICA_BOLD,
        helvetica_italic = FL_HELVETICA_ITALIC,
        helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
        courier = FL_COURIER,
        courier_bold = FL_COURIER_BOLD,
        courier_italic = FL_COURIER_ITALIC,
        courier_bold_italic = FL_COURIER_BOLD_ITALIC,
        times = FL_TIMES,
        times_bold = FL_TIMES_BOLD,
        times_italic = FL_TIMES_ITALIC,
        times_bold_italic = FL_TIMES_BOLD_ITALIC,
        symbol = FL_SYMBOL,
        screen = FL_SCREEN,
        screen_bold = FL_SCREEN_BOLD,
        zapf_dingbats = FL_ZAPF_DINGBATS,
    };

    Font(Font_type);
    Font(int font_type);

    int as_int() const;

private:
    int f;  // font
};

// ----------------------------------------------------------------

class Shape {
public:
    void draw() const;
    virtual void move(int dx, int dy);

    int number_of_points() const;
    Point point(int i) const;

    Color color() const;
    Line_style style() const;
    Color fill_color() const;

    void set_color(Color);
    void set_style(Line_style);
    void set_fill_color(Color);

    virtual ~Shape() {};

protected:
    Shape() {};
    Shape(initializer_list<Point> lst);

    void add(Point);
    void set_point(int nth, Point);
    virtual void draw_lines() const;

private:
    vector<Point> points;
    Color lcolor {fl_color()};          // line color
    Line_style ls {Line_style::solid};
    Color fcolor {Color::invisible};    // fill color
};

// ----------------------------------------------------------------

struct Line : Shape {
    Line(Point, Point);
};


struct Lines : Shape {
    Lines();
    Lines(initializer_list<pair<Point, Point>> lst);

    void draw_lines() const;
    void add(Point, Point);
};

// ----------------------------------------------------------------

struct Open_polyline : Shape {
    Open_polyline();
    Open_polyline(initializer_list<Point> lst);

    void add(Point);
};


struct Closed_polyline : Open_polyline {
    using Open_polyline::Open_polyline;

    void draw_lines() const;
};


struct Polygon : Closed_polyline {
    Polygon();
    Polygon(initializer_list<Point> lst);

    void add(Point);
};

// ----------------------------------------------------------------

struct Rectangle : Shape {
    Rectangle(Point top_left, int width, int height);
    Rectangle(Point top_left, Point bottom_right);

    void draw_lines() const;

    int height() const;
    int width() const;

private:
    int h;  // height
    int w;  // width
};

// ----------------------------------------------------------------

struct Text : Shape {
    Text(Point bottom_left, const string& label);

    void draw_lines() const;

    void set_label(const string&);
    void set_font(Font);
    void set_font_size(int size);

    string label() const;
    Font font() const;
    int font_size() const;

private:
    string lab;     // label
    Font fnt {fl_font()};
    int fnt_sz {(fl_size() < 14) ? 14 : fl_size()};
};

// ----------------------------------------------------------------

struct Circle : Shape {
    Circle(Point center, int radius);

    void draw_lines() const;

    Point center() const;
    int radius() const;

    void set_radius(int radius);

private:
    int r;  // radius
};


struct Ellipse : Shape {
    Ellipse(Point center, int x_radius, int y_radius);

    void draw_lines() const;

    Point center() const;
    Point focus_p() const;
    Point focus_m() const;

    void set_x_radius(int);
    void set_y_radius(int);

    int x_radius() const;
    int y_radius() const;

private:
    int w;      // radius on x-axis
    int h;      // radius on y-axis
};


// ----------------------------------------------------------------

}   // END of ``namespace Graph_lib''


#endif  // GRAPH_GUARD
