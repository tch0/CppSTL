#include <iostream>
#include <iterator>
#include <regex>
using namespace std;

// regex_token_iterator<BidirIt, CharT, Traits>
// predefined instantiation: 
// s, c, ws, wc
// operator* get sub_match

// the 4-th argument: 
// -1 : focus on string between sperators(aka between the matched subexpressions)
// 0  : full match
// n  : the n-th matched subexpression

int main(int argc, char const *argv[])
{
    string data = "<Person>\n"
           "<first>Nico</first>\n"
           "<last>Josuttis</last>\n"
           "</person>";
    regex reg(R"(<(.*)>(.*)</(\1)>)");

    sregex_token_iterator pos(data.cbegin(), data.cend(), reg, {0, 2}); // 0: full match, 2: second substring
    sregex_token_iterator end;
    for (; pos != end; ++pos)
    {
        cout << "match: " << pos->str() << endl;
    }
    
    cout << endl;
    string names = "nico, jim . helmut, pual. tim ; john paul, rita";
    regex sep(R"([ \t\n]*[,;.][ \t\n]*)");
    sregex_token_iterator p(names.cbegin(), names.cend(), sep, -1); // -1: values between sperators
    for_each(p, end, [](const ssub_match& m){
        cout << "name: " << m << endl; // ssub_match can explicitly cast to string.
    });
    
    return 0;
}
