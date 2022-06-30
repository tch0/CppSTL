#include <iostream>
#include <functional>
using namespace std;

// pre-defined function objects
// negate -
// plus +
// minus -
// multiplies *
// divides /
// equal_to ==
// not_equal_to !=
// less <
// greater >
// less_equal <=
// greater_equal >=
// logical_and &&
// logical_or ||
// logical_not !
// bit_and &
// bit_or |
// bit_xor ^

int main(int argc, char const *argv[])
{
    cout << boolalpha;
    cout << less<int>()(1, 2) << endl;
    cout << plus<double>()(1.0, 2.0) << endl;
    cout << hex << bit_xor<int>()(0xff00, 0x00ff) << endl;
    return 0;
}