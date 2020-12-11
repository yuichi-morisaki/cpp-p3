#include "Graph.h"

// ----------------------------------------------------------------

Color::Color(Color_type cc)
    : c {Fl_Color {cc}}, v {visible}
{
}

Color::Color(Color_type cc, Transparency vv)
    : c {Fl_Color {cc}}, v {vv}
{
}

Color::Color(int cc)
    : c {Fl_Color(cc)}, v {visible}
{
}

Color::Color(Transparency vv)
    : c {Fl_Color()}, v {vv}
{
}


int Color::as_int() const {
    return c;
}

char visibility() const {
    return v;
}

void set_visibility(Transparency vv) {
    v = vv;
}

// ----------------------------------------------------------------

Line_style::Line_style(Line_style_type lst)
    : s {lst}, w {0}
{
}

Line_style::Line_style(Line_style_type lst, int ww)
    : s {lst}, w {ww}
{
}

Line_style::Line_style(int ss)
    : s {ss}, w {0}
{
}

int Line_style::width() const {
    return w;
}

int Line_style::style() const {
    return s;
}

// ----------------------------------------------------------------

Line::Line(Point p1, Point p2) {
    add(p1);
    add(p2);
}

// ----------------------------------------------------------------

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

// ----------------------------------------------------------------

void Open_polyline::add(Point p) {
    Shape::add(p);
}

// ----------------------------------------------------------------

void Closed_polyline::draw_lines() const {
    Open_polyline::draw_lines();

    if (2 < number_of_points() && color().visibility())
        fl_line(point(number_of_points()-1).x,
                point(number_of_points()-1).y,
                point(0).x,
                point(0).y);
}

// ----------------------------------------------------------------

void Polygon::add(Point p) {
    // TODO
    // check that the new line doesn't intersect existing lines

    Closed_polyline::add(p);
}

// ----------------------------------------------------------------

Rectangle::Rectangle(Point xy, int ww, int hh)
    : w {ww}, h {hh}
{
    if (h <= 0 || w <= 0)
        error("Bad rectangle: non-positive side");
    add(xy);
}

Rectangle::Rectangle(Point x, Point y)
    : w {y.x - x.x}, h {y.y - x.y}
{
    if (h <= 0 || w <= 0)
        error("Bad rectangle: first point is not top left");
    add(x);
}

void Rectangle::draw_lines() const {
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x, point(0).y, w, h);
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_rect(point(0).x, point(0).y, w, h);
    }
}

int Rectangle::height() const {
    return h;
}

int Rectangle::width() const {
    return w;
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

int Font::as_int() const {
    return f;
}

// ----------------------------------------------------------------

Text::Text(Point x, const string& s)
    : lab {s}
{
    add(x);
}

void Text::draw_lines() const {
    fl_draw(lab.c_str(), point(0).x, point(0).y);
}

void Text::set_label(const string& s) {
    lab = s;
}

string Text::label() const {
    return lab;
}

void Text::set_font(Font f) {
    fnt = f;
}

Font Text::font() const {
    return fnt;
}

void Text::set_font_size(int s) {
    fnt_sz = s;
}

int Text::font_size() const {
    return fnt_sz;
}

// ----------------------------------------------------------------

Circle::Circle(Point p, int rr)
    : r {rr}
{
    add(Point {p.x - r, p.y - r});
}

void Circle::draw_lines() const {
    if (color().visibility())
        fl_arc(point(0).x, point(0).y, r+r, r+r, 0, 360);
}

Point Circle::center() const {
    return {point(0).x + r, point(0).y + r};
}

int Circle::radius() const {
    return r;
}

void Circle::set_radius(int rr) {
    // maintain the center
    set_point(0, Point {center().x - rr, center().y - rr});

    r = rr;
}

// ----------------------------------------------------------------

Ellipse::Ellipse(Point p, int w, int h)
{
    // TODO
}

void Ellipse::draw_lines() const {
    // TODO
}

Point Ellipse::center() const {
    // TODO
}

Point Ellipse::focus1() const {
    if (h <= w)
        return {center().x + int(sqrt(double(w*w-h*h))),
                center().y};
    else
        return {center().x,
                center().y + int(sqrt(double(h*h-w*w)))};
}

Point Ellipse::focus2() const {
    // TODO
}

void Ellipse::set_major(int ww) {
    set_point(0, Point {center().x - ww, center().y - h});

    w = ww;
}

int Ellipse::major() const {
    return w;
}

void Ellipse::set_minor(int hh) {
    set_point(0, Point {center().x - w, center().y - hh});

    h = hh;
}

int Ellipse::minor() const {
    return h;
}

// ----------------------------------------------------------------

Marked_polyline::Marked_polyline(const string& m)
    : mark {m}
{
    if (m == "")
        mark = "*";
}

Marked_polyline::Marked_polyline(
        const string& m, initializer_list<Point> lst)
    : Open_polyline {lst}, mark {m}
{
    if (m == "")
        mark = "*";
}

void draw_mark(Point xy, char c) {
    constexpr int dx = 4;
    constexpr int dy = 4;
    string m(1, c);     // string holding the single char c
    fl_draw(m.c_str(), xy.x - dx, xy.y + dy);
}

void Marked_polyline::draw_lines() const {
    Open_polyline::draw_lines();
    for (int i = 0; i < number_of_points(); ++i)
        draw_mark(point(i), mark[i % mark.size()]);
}

// ----------------------------------------------------------------

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

Mark::Mark(Point xy, char c)
    : Marks {string(1, c)}
{
    add(xy);
}

// ----------------------------------------------------------------

struct Bad_image::Bad_image(int h, int w)
    : Fl_Image {h, w, 0}
{
}

void Bad_image::draw(int x, int y, int, int, int, int) {
    draw_empty(x, y);
}

bool can_open(const string& s) {
    ifstream ifs(s);
    return ifs.is_open();
}

Image::Image(Point xy, string file_name, Suffix e = Suffix::none)
    : w {0}, h {0}, fn {xy, ""}
{
    add(xy);

    if (!can_open(s)) {
        fn.set_label("cannot open\"" + file_name + '"');
        p = new Bad_image(30, 20);
        return;
    }

    if (e == Suffix::none)
        e = get_encoding(s);

    switch(e) {
        case Suffix::jpg:
            p = new Fl_JPEG_Image {file_name.c_str()};
            break;
        case Suffix::gif:
            p = new Fl_GIF_Image {file_name.c_str()};
            break;
        default:
            fn.set_label("unsupported file type\"" + file_name + '"');
            p = new Bad_image {30, 20};
    }
}

Image::~Image() {
    delete p;
}

void Image::draw_lines() const {
    // TODO
}

void Image::set_mask(Point xy, int ww, int hh) {
    w = ww;
    h = hh;
    cx = xy.x;
    cy = xy.y;
}
