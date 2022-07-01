#include <iostream>
#include <regex>
#include <string>
#include <iterator>
using namespace std;

// type of regex: regex<charT, regex-trait>
// predefined instantiation: 
// regex: basic_regex<char>
// wregex: basci_regex<wchar_t>

// regex_traits encapsulate the locale triats of regex

// the type of match results: match_results<the-char-iterator>
// predefined instantiation:
// smatch: match_results<string::const_iterator>
// cmatch: match_results<const char*>
// wcmatch: match_results<const wchar_t*>
// wsmatch: match_results<wstring::const_iterator>

// the type of subexpression: sub_match<the-chat-iterator>
// predefined instantiation: csub_match, ssub_match, wcsub_match, wssub_match

// get the whole matched string from match_results m:
//      m.str(), m.str(0), m[0].str(), *(m.begin())
// get the n-th matched substring from match_results m:
//      m.str(1), m[1].str(), *(m.begin()+1)

int main(int argc, char const *argv[])
{
    string data = "XML tag: <tag-name>the value</tag-name>";
    smatch m; // smatch is match_results<string::const_iterator>

    bool found = regex_search(data, m, regex(R"(<(.*)>(.*)</(\1)>)")); // 3 groups
    cout << boolalpha;
    cout << "found: " << found << endl; // true
    cout << "m.empty(): " << m.empty() << endl; //false
    cout << "m.size(): " << m.size() << endl; // 3
    cout << "m.position(): " << m.position() << endl;
    cout << "m.prefix().str(): " << m.prefix().str() << endl; // XML tag: 
    cout << "m.suffix().str(): " << m.suffix().str() << endl; // 
    cout << endl;

    for (int i = 0; i < m.size(); ++i)
    {
        cout << "m[" << i << "].str(): " << m[i].str() << endl;
        cout << "m.str(" << i << "): " << m.str(i) << endl;
        cout << "m.position(" << i << "): " << m.position(i) << endl;
    }
    cout << endl;

    // iterating all matches
    //      first ssub_match is the whole string.
    //      rest are all groups.
    cout << "matches: " << endl;
    for (auto pos = m.begin(); pos != m.end(); ++pos)
    {
        cout << "  " << *pos << " ";
        cout << "(length:" << pos->length() << ")" << endl;
    }
    cout << endl;

    // second example:
    // will match <first>Nico</first> and <last>Josuttis</last>
    // greedy match: if there is no \n or the value subexpression is something that can match \n (e.g. [^<]*), will match the whole string.
    data = "<Person>\n"
           "<first>Nico</first>\n"
           "<last>Josuttis</last>\n"
           "</person>";
    regex reg(R"(<(.*)>(.*)</(\1)>)");
    auto pos = data.cbegin();
    auto end = data.cend();
    for(; regex_search(pos, end, m, reg); pos = m.suffix().first) // m.suffix().first equals to m[0].second
    {
        cout << "match: " << m.str() << endl;
        cout << "tag: " << m.str(1) << endl;
        cout << "value: " << m.str(2) << endl;
    }
    return 0;
}