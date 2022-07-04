#include <iostream>
#include <iomanip>
using namespace std;

// every stream hold a locale object.
// imbue(loc): set locale obejct
// getloc(): get locale object

// internationalization functions of stream:
// widen(c): convert char c to character in stream charset
// narrow(c, def): convert character c in stream charset to char

int main(int argc, char const *argv[])
{
    cout << cout.widen('\n') << "next" << endl;
    return 0;
}
