#include <iostream>
#include <limits> // for numeric_limits template
#include <string>
using namespace std;

// numeric_limits template
// meaningless general template version
// specialization for all numeric types: bool,char,char32_t,...,int,...,double,...,long double

class Foo {};

int main(int argc, char const *argv[])
{
    cout << numeric_limits<int>::min() << endl; // it's a static constexpr function
    cout << numeric_limits<int>::max() << endl;
    cout << boolalpha << numeric_limits<Foo>::is_specialized << endl;
    cout << numeric_limits<int>::is_specialized << endl; // static constexpr member
    cout << numeric_limits<int>::is_signed << endl;
    cout << numeric_limits<int>::is_integer << endl;
    cout << numeric_limits<int>::is_exact << endl; // true
    cout << numeric_limits<int>::is_bounded << endl; // true for all built-in types
    cout << numeric_limits<int>::is_modulo << endl; // false
    cout << numeric_limits<unsigned>::is_modulo << endl; // true
    cout << numeric_limits<int>::is_iec559 << endl; // false
    cout << numeric_limits<double>::is_iec559 << endl; // true, IEC 559 aka IEEE 754
    cout << numeric_limits<long double>::is_iec559 << endl; // true
    cout << numeric_limits<int>::radix << endl; // almost always 2
    cout << numeric_limits<double>::signaling_NaN() << endl; // nan
    cout << numeric_limits<int>::digits10 << " " << numeric_limits<int>::digits << endl; // 9 31
    cout << numeric_limits<double>::digits10 << " " << numeric_limits<double>::digits << endl; // 15 53

    cout << numeric_limits<char>::is_signed << endl; // true, in this situation, char is signd char.

    cout << numeric_limits<string>::is_specialized << endl; // false, not specialized for string
    return 0;
}
