#include "calculator.h"
#include <iostream>
#include <stdexcept>

using namespace std;


int main()
try {
    Token_stream ts {cin};

    calculate(ts);

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
