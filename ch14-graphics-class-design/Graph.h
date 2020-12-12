#include "Point.h"

#include <FL/fl_draw.H>

#include <initializer_list>
#include <vector>

using namespace std;

namespace Graph_lib {

    // ------------------------------------------------------------
    //  Line style

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

    // ------------------------------------------------------------
    //  Color

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

            enum Transparency {
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

    // ------------------------------------------------------------

    class Shape {
        public:
            void draw() const;
            virtual void move(int dx, int dy);

            void set_style(Line_style);
            Line_style style() const;

            void set_color(Color);
            Color color() const;

            void set_fill_color(Color);
            Color fill_color() const;

            Point point(int nth) const;
            int number_of_points() const;

            Shape(const Shape&) = delete;   // prevent copying
            Shape& operator=(const Shape&) = delete;

            virtual ~Shape() {}

        protected:
            Shape() {}
            Shape(initializer_list<Point> lst);

            virtual void draw_lines() const;
            void add(Point p);
            void set_point(int nth, Point p);

        private:
            vector<Point> points;
            Line_style ls {0};
            Color lcolor {Color(fl_color())};
            Color fcolor {Color::invisible};
    };

    // ------------------------------------------------------------

    class Line : public Shape {
        public:
            Line(Point, Point);
    };


    class Lines : public Shape {
        public:
            Lines();
            Lines(initializer_list<pair<Point, Point>>);

            void draw_lines() const override;
            void add(Point, Point);
    };

    // ------------------------------------------------------------

}   // End of namespace Graph_lib
