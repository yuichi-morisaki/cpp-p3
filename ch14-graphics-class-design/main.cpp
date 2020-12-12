#include "Graph.h"

#include <iostream>
#include <stdexcept>

using namespace std;

using namespace Graph_lib;

int main()
try {

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "error\n";
    return 2;
}
