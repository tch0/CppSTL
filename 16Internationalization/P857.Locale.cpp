#include <iostream>
#include <locale> // for locale
#include <exception>
#include <cstdlib>
using namespace std;

// in <locale>
// locale: encapsulate conversion between different nations and clutures
// format of locale string: language[_area[.code]][@modifier]
//      may different between different OS
//      use this construct a locale object
// example:
//      C (a special one in C++, means the C classic locale)
//      de_DE germany
//      zh_CN chinese, mainland
//      zh_TW chinese, TaiWan
//      POSIX POSIX convension(English, 7bit)
//      more...

// notice: you may got a [Exception: locale::facet::_S_create_c_locale name not valid] from gcc on windows.
//         GCC on non-GNU platform does not have a good enough local support.

// facet:
//      a particular aspect of locale call facet, locale plays a role of container of facets.

int main(int argc, char const *argv[])
{
    try
    {
        // use the classic C locale for cin, or locale("C") for C classic locale
        // locale("")/locale() for native environment locale
        // echo %LANG% for native locale on windows
        cin.imbue(locale::classic()); 

#ifdef _MSC_VER
        cout.imbue(locale("deu_deu.1252")); // for Windows
#else
        cout.imbue(locale("de_DE")); // for POSIX/Unix-like
#endif

        // Germany use , as point of floating pointer number
        cout << "input floating pointer number(classic notation .): " << endl;
        double value = 0;
        while (cin >> value)
        {
            cout << value << endl; // point will be ,
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return 0;
}
