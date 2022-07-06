#include <iostream>
#include <locale>
using namespace std;

// details of locale:
// locale is immutable, means that no method to modify facet inside the locale (but locale can be assigned)
// if you want to get a new locale based on an existing locale, just construct a new locale with the existing locale as argument.
// copying is a cheap operation for locale.

// get facet inside a locale:
// has_facet<F>(loc) -> bool
// use_facet<F>(loc) -> F&, if F doest not exist inside loc, throw a bad_cast
//      F is type of the facet you want to get.
//      the facet type must be passed explicitly, so it's type-safe interfaces.

int main(int argc, char const *argv[])
{
    locale loc; // get global locale
    locale loc2 = locale::classic();
    cout << loc.name() << endl; // C
    cout<< loc2.name() << endl;
    
    cout << boolalpha << loc("hello"s, "world"s) << endl; // true, use std::locale::operator() compare two stringss

    locale loc3();

    return 0;
}
