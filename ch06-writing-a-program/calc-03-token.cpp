#include <token-stream.h>
#include <iostream>

using namespace std;

int main()
try {
    Token_stream ts;

    while (cin) {
        Token t = ts.get();
        if (t.kind == '8')
            cout << t.value << '\n';
        else
            cout << t.kind << '\n';
        if (t.kind == 'q')
            break;
        if (t.kind == '8' && t.value == 4) {
            ts.putback(t);
            ts.putback(t);
        }
        if (t.kind == '8' && int(t.value) % 2 == 1) {
            ts.putback(t);
            t = ts.get();
            cout << t.value << '\n';
        }
    }

    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "exception\n";
    return 2;
}
