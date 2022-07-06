#include <iostream>
#include <locale>
#include <iomanip>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

// category: ctype
// character classification: ctype<>
// character conversion: codecvt<>

// ctype<charT>:
// 1. conversions between char and charT
//      widen() from char to charT
//      narrow() from charT to char
// 2. character classfication
// 3. case conversion function of character
//      toupper
//      tolower

wstring to_wstring(const string& str, const locale& loc = std::locale())
{
    vector<wchar_t> buf(str.size());
    use_facet<ctype<wchar_t>>(loc).widen(str.data(), str.data() + str.size(), buf.data());
    return wstring(buf.data(), buf.size());
}

string to_string(const wstring& str, const locale& loc = std::locale())
{
    vector<char> buf(str.size());
    use_facet<ctype<wchar_t>>(loc).narrow(str.data(), str.data() + str.size(), '?', buf.data()); // ? for the characters that do not have a corresponding char
    return string(buf.data(), buf.size());
}

// character encoding conversion:
// codecvt<> : mutual conversion between internal representation and external representation.
// used in basic_filebuf for internal representation of programs and file representation.

int main(int argc, char const *argv[])
{
    // ctype
    locale loc;
    string s = "hello";
    for (auto& c : s)
    {
        c = use_facet<ctype<char>>(loc).toupper(c);
    }
    cout << s << endl;

    // narrow widen
    wstring ws = to_wstring(s);
    wcout << ws << endl;
    cout << to_string(ws) << endl;  

    // character encoding conversion
    return 0;
}
