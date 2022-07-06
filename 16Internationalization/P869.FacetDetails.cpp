#include <iostream>
#include <locale>
#include <iomanip>
using namespace std;

// a facet class must:
// 1. public inherit std::locale::facet class
// 2. must have a public static member named id whose type is locale::id, used for index in locale object.
//          inside locale, there also normal contianer, but it supply a type-safe interfaces for visiting.

// principle(convention) of writing a facet class:
// 1. all member function declares as const, use_facet<> will return a const facet object.
// 2. all public functions are not virtual (NVI, non-virtual interface), but delegate real operations to a 
//          virtual protected function which is named with a do_ prefix and can be overrided in derived classes.

// Most standard facet has a _byname version class which is derived from standard facet,
// used for building facet instantiation from corresponding locale name, and which is used in construtor of locale (the version of accepting locale name).
//      e.g. numpunct_byname("de_DE")

// numeric formatting:
// numpunct: deal with the punctuation related to numeric formatting and numeric parsing
// num_put: numeric formatting
// num_get: numeric parsing

// numeric puntuation:
// typical implementation in Germany, using , as decimal point, ussing , as thousands seperator
template<typename CharT>
class SelfDefinedNumpuct : public numpunct<CharT>
{
public:
    // decimal point
    virtual CharT do_decimal_point() const override
    {
        return ',';
    }
    // thousands seperator
    virtual CharT do_thousands_sep() const override
    {
        return '.';
    }
    // grouping of numeric numbers (seperated with thousands seperator)
    virtual string do_grouping() const override
    {
        return {3, 2, 3}; // equivalent to "\3\2\3"
    }
    // output name of boolean true
    virtual string do_truename() const override
    {
        return "MyTrue";
    }
    // output name of boolean false
    virtual string do_falsename() const override
    {
        return "MyFalse";
    }
};

// num_put and num_get also can be derived.

int main(int argc, char const *argv[])
{
    locale loc = cin.getloc();
    cout << loc.name() << endl; // C

    // numeric punctuation
    locale newLoc(loc, new SelfDefinedNumpuct<char>());
    ostream numOut(cout.rdbuf());
    numOut.imbue(newLoc);
    numOut << "numOut: " << setprecision(10) << 1000000.935 << endl; // 10.00.000,935
    numOut << "bool: " << boolalpha << true << " " << false << endl; // MyTrue MyFalse
    cout << "cout: " << setprecision(10) << 1000000.935 << endl; // 1000000.935
    cout << "bool: " << boolalpha << true << " " << false << endl; // true false

    // numeric formatting
    use_facet<num_put<char>>(loc).put(cout, cout, '_', 1234.5678); // 1234.5678
    cout << endl;

    // numeric parsing
    ios_base::iostate err = ios_base::goodbit;
    double val = 0;
    use_facet<num_get<char>>(cin.getloc()).get(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), cin, err, val);
    cout << "parsed value: " << val << endl;
    return 0;
}
