#ifndef IMAGE_GUARD
#define IMAGE_GUARD

#include "point.h"
#include "graph.h"

#include <string>

using std::string;


namespace Graph_lib {

enum class Suffix {
    none,
    jpg,
    gif,
};


struct Image : Shape {
    Image(Point, string file_name, Suffix e = Suffix::none);
    ~Image();

    void draw_lines() const;

    void set_mask(Point, int width, int height);

private:
    int w;  // define "masking box" within image
    int h;  //   relative to position (cx, cy)
    int cx;
    int cy;
    Fl_Image* p;
    Text fn;
};


struct Bad_image : Fl_Image {
    Bad_image(int h, int w);
    void draw(int x, int y, int, int, int, int);
};

}   // END of ``namespace Graph_lib''

#endif  // IMAGE_GUARD
