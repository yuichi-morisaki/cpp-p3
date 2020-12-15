#include "image.h"

#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>

#include <cstring>
#include <fstream>

using std::ifstream;


namespace Graph_lib {

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

Suffix get_encoding(const string& file_name)
{
    struct SuffixMap {
        const char* extension;
        Suffix suffix;
    };

    static SuffixMap smap[] = {
        {".jpg",  Suffix::jpg},
        {".jpeg", Suffix::jpg},
        {".gif",  Suffix::gif},
    };

    for (int i = 0, n = ARRAY_SIZE(smap); i < n; i++) {
        int len = strlen(smap[i].extension);
        int fn_len = file_name.length();
        string suffix = file_name.substr(fn_len - len, len);
        if (fn_len >= len && suffix == smap[i].extension)
            return smap[i].suffix;
    }

    return Suffix::none;
}

bool can_open(const string& file_name)
{
    ifstream ifs {file_name};
    return ifs.is_open();
}

Image::Image(Point xy, string file_name, Suffix e)
    : w {0},
      h {0},
      fn {xy, ""}
{
    add(xy);

    if (!can_open(file_name)) {
        fn.set_label("cannot open\"" + file_name + '"');
        p = new Bad_image(30, 20);
        return;
    }

    if (e == Suffix::none)
        e = get_encoding(file_name);

    switch (e) {
    case Suffix::jpg:
        p = new Fl_JPEG_Image(file_name.c_str());
        break;
    case Suffix::gif:
        p = new Fl_GIF_Image(file_name.c_str());
        break;
    default:
        fn.set_label("unsupported file type\"" + file_name + '"');
        p = new Bad_image(30, 20);
        break;
    }
}


Image::~Image()
{
    delete p;
}


void Image::draw_lines() const
{
    if (fn.label() != "")
        fn.draw_lines();

    if (w && h)
        p->draw(point(0).x, point(0).y, w, h, cx, cy);
    else
        p->draw(point(0).x, point(0).y);
}


void Image::set_mask(Point xy, int ww, int hh)
{
    w = ww;
    h = hh;
    cx = xy.x;
    cy = xy.y;
}


Bad_image::Bad_image(int h, int w)
    : Fl_Image {h, w, 0}
{
}


void Bad_image::draw(int x, int y, int, int, int, int)
{
    draw_empty(x, y);
}

}   // END of ``namespace Graph_lib''
