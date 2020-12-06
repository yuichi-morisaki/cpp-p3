#include "token.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main()
try {
    Token_stream ts {cin};

    while (true) {
        Token t = ts.get();
        if (t.kind == QUIT)
            break;
        cout << "'" << t.kind << "' "
             << "(" << t.value << ") "
             << "``" << t.name << "''\n";
    }

    return 0;
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
