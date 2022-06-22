#include <iostream>
#include <ratio>
#include <limits>
using namespace std;

// <ratio>
// compile-time fraction computation
// automatic simplification
// negative always be numerator
// basic operations: +-*/ ==> ratio_add/ratio_substract/ratio_nultiply/ratio_divide (::type get ratio<N, D>)
// comparison: ratio_equal/xxx_not_equal/..._less/_less_equal/_greater/_greater_equal (::value get std::true_type/std::false_type)

// class template ratio will catch all errors:
// denominator be 0
// overflow
// etc.

// pre-defined units: deci(1/10), centi(1/100), milli(1/1,000), micro(1/1,000,000), nano(1/1,000,000,000), pico(1/1,000,000,000,000), ... (femto, atto, zepto, yocto)
//                    deca(100), hecto(100), kilo(1,000), mega(1,000,000), giga(1,000,000,000), tera(1,000,000,000,000), ... (peta, exa, zetta, yotta)

template<intmax_t N, intmax_t D>
void printRatio(const ratio<N, D>& r)
{
    using type = typename ratio<N, D>::type;
    cout << type::num << "/" << type::den << endl;
}

int main(int argc, char const *argv[])
{
    using FiveThirds = ratio<10,6>; // automatic simplification
    printRatio(FiveThirds());

    using zero = ratio<0>;
    printRatio(zero()); // 0/1

    using Neg = ratio<7, -3>;
    printRatio(Neg()); // -7/3

    using res = ratio_add<ratio<3,5>, ratio<2,3>>::type;
    printRatio(res()); // 19/15
    using res2 = ratio_divide<ratio<3,5>, ratio<5, 9>>::type; // 27/25
    printRatio(res2());

    cout << boolalpha;
    cout << ratio_equal<ratio<5,3>, ratio<10,6>>::value << endl; // true
    cout << ratio_greater_equal<ratio<5,3>, ratio<3,2>>::value << endl; // true

    // errors
    // using mulres = ratio_multiply<ratio<numeric_limits<intmax_t>::max(), 1>, ratio<2>>::type;
    // cause : static assertion failed: overflow in multiplication

    // using divres = ratio_divide<ratio<1>, ratio<0>>::type;
    // cause: static assertion failed: division by 0

    // pre-defined ratio
    printRatio(std::nano());
    printRatio(std::giga());
    return 0;
}