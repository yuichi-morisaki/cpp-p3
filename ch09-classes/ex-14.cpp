#include "money.h"

int main()
{
    Money m0 {};
    cout << m0 << '\n';

    Money m1 {123, 45.67890};
    cout << m1 << '\n';

    Money m2 {987, 65.43210};
    cout << m2 << '\n';

    return 0;
}
