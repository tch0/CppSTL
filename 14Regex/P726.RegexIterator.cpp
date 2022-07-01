#include <iostream>
#include <regex>
#include <string>
#include <iterator>
using namespace std;

// regex_iterator<BidirIt, charT, Traits>: construct and operator++ will call regex_search
// predefined instantiation:
// sregex_iterator, cregex_iterator, wsregex_iterator, wcregex_iterator
// operator* return a match_results object.

// it's a bidirectional iterator

int main(int argc, char const *argv[])
{
    string data = "<Person>\n"
           "<first>Nico</first>\n"
           "<last>Josuttis</last>\n"
           "</person>";
    regex reg(R"(<(.*)>(.*)</(\1)>)");

    sregex_iterator pos(data.cbegin(), data.cend(), reg); // will call regex_search
    sregex_iterator end;
    for (; pos != end; ++pos)
    {
        cout << "match: " << pos->str() << endl;
        cout << "tag: " << pos->str(1) << endl;
        cout << "value: " << pos->str(2) << endl;
    }
    cout << endl;

    // use a regex_iterator to process each matched substring as element in an algorithm
    sregex_iterator beg(data.cbegin(), data.cend(), reg);
    for_each(beg, end, [](const smatch& m) {
        cout << "match: " << m.str() << endl;
        cout << "tag: " << m.str(1) << endl;
        cout << "value: " << m.str(2) << endl;
    });

    return 0;
}
