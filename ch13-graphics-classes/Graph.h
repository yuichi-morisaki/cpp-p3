class Color {
    public:
        enum Color_type {
            white = FL_WHITE,
            black = FL_BLACK,
            red = FL_RED,           dark_red = FL_DARK_RED,
            blue = FL_BLUE,         dark_blue = FL_DARK_BLUE,
            green = FL_GREEN,       dark_green = FL_DARK_GREEN,
            yellow = FL_YELLOW,     dark_yellow = FL_DARK_YELLOW,
            magenta = FL_MAGENTA,   dark_magenta = FL_DARK_MAGENTA,
            cyan = FL_CYAN,         dark_cyan = FL_DARK_CYAN,
        };

        enum Trasparency {
            invisible = 0,
            visible = 255,
        };

        Color(Color_type cc);
        Color(Color_type cc, Transparency vv);
        Color(int cc);
        Color(Transparency vv);

        int as_int() const;
        char visibility() const;
        void set_visibility(Transparency vv);

    private:
        char v;     // visibility
        Fl_Color c;
};

// ----------------------------------------------------------------

class Line_style {
    public:
        enum Line_style_type {
            solid = FL_SOLID,           // ---------
            dash = FL_DASH,             // - - - - -
            dot = FL_DOT,               // .........
            dashdot = FL_DASHDOT,       // - . - . -
            dashdotdot = FL_DASHDOTDOT, // -..-..-..
        };

        Line_style(Line_style_type ss);
        Line_style(Line_style_type lst, int ww);
        Line_style(int ss);

        int width() const;
        int style() const;

    private:
        int s;
        int w;
};

// ----------------------------------------------------------------


class Shape {
    // Chapter 14
    // void add(Point);
    // int number_of_points() const;
    // const Point& point(int) const;
    // Color color() const;
    // Color fill_color() const;
};


// ----------------------------------------------------------------

struct Line : Shape {
    Line(Point p1, Point p2);
};

// ----------------------------------------------------------------

struct Lines : Shape {
    Lines();
    Lines(initializer_list<pair<Point, Point>> lst);

    void draw_lines() const;
    void add(Point p1, Point p2);
};

// ----------------------------------------------------------------

struct Open_polyline : Shape {
    using Shape::Shape;     // use Shape's constructor

    void add(Point p);
};

// ----------------------------------------------------------------

struct Closed_polyline : Open_polyline {
    using Open_polyline::Open_polyline;

    void draw_lines() const;
};

// ----------------------------------------------------------------

struct Polygon : Closed_polyline {
    using Closed_polyline::Closed_polyline;

    void add(Point p);
    void draw_lines() const;
};

// ----------------------------------------------------------------

class Rectangle : Shape {
    public:
        Rectangle(Point xy, int ww, int hh);
        Rectangle(Point x, Point y);

        void draw_lines() const;
        int height() const;
        int width() const;

    private:
        int h;
        int w;
};

// ----------------------------------------------------------------

class Font {
    public:
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

        Font(Font_type ff);
        Font(int ff);

        int as_int() const;

    private:
        int f;
};

// ----------------------------------------------------------------

class Text : Shape {
    public:
        Text(Point x, const string& s);

        void draw_lines() const;

        void set_label(const string& s);
        string label() const;

        void set_font(Font f);
        Font font() const;

        void set_font_size(int s);
        int font_size() const;

    private:
        string lab;     // label
        Font fnt {fl_font()};
        int fnt_sz {fl_size() < 14} ? 14 : fl_size();
};

// ----------------------------------------------------------------

class Circle : Shape {
    public:
        Circle(Point p, int rr);

        void draw_lines() const;

        Point center() const;
        int radius() const;
        void set_radius(int rr);

    private:
        int r;
};

// ----------------------------------------------------------------

class Ellipse : Shape {
    public:
        Ellipse(Point p, int w, int h);

        void draw_lines() const;

        Point center() const;
        Point focus1() const;
        Point focus2() const;

        void set_major(int ww);
        int major() const;

        void set_minor(int hh);
        int minor() const;

    private:
        int w;
        int h;
};

// ----------------------------------------------------------------

class Marked_polyline : Open_polyline {
    public:
        Marked_polyline(const string& m);
        Marked_polyline(const string& m,
                        initializer_list<Point> lst);

        void draw_lines(const);

    private:
        string mark;
};

// ----------------------------------------------------------------

struct Marks : Marked_polyline {
    Marks(const string& m);
    Marks(const string& m, initializer_list<Point> lst);
};

// ----------------------------------------------------------------

struct Mark : Marks {
    Mark(Point xy, char c);
};

// ----------------------------------------------------------------

struct Bad_image : Fl_Image {
    Bad_image(int h, int w);
    void draw(int x, int y, int, int, int, int);
};


enum class Suffix {
    none,
    jpg,
    gif,
};

class Image : Shape {
    public:
        Image(Point xy, string file_name, Suffix e = Suffix::none);
        ~Image();
        void draw_lines() const;
        void set_mask(Point xy, int ww, int hh);

    private:
        int w;
        int h;
        int cx;
        int cy;
        Fl_Image* p;
        Text fn;
};
