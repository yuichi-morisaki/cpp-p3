#include <iostream>
#include <stdexcept>

using namespace std;

void error(string s1, string s2)
{
    throw runtime_error(s1 + " " + s2);
}

// runtime error: Woops! demonstration of function 'error()'
int main()
try {
    error("Woops!",
          "demonstration of function 'error()'");

    return 0;
}
catch (runtime_error& e) {
    cerr << "runtime error: " << e.what() << '\n';
    return 1;
}

/*
// If we don't catch an exception
//
// terminate called after throwing an instance of 'std::runtime_error'
//   what(): Woops! what the hell!
// Aborted (core dumped)
int main()
{
    error("Woops!", "what the hell!");
}
*/
