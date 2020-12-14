#ifndef POINT_GUARD
#define POINT_GUARD

namespace Graph_lib {

struct Point {
    int x;
    int y;
};

bool operator==(Point, Point);

bool operator!=(Point, Point);

}   // END of ``namespace Graph_lib''

#endif  // POINT_GUARD
