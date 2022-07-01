#include <iostream>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <cctype>
using namespace std;

// template basic_string<charT, char_trait, allocator>

// bulid our own char_traits class

struct ignorecases_traits : public std::char_traits<char>
{
    // equal: ==
    static bool eq(const char& c1, const char& c2)
    {
        return toupper(c1) == toupper(c2);
    }
    // less than: <
    static bool lt(const char& c1, const char& c2)
    {
        return toupper(c1) < toupper(c2);
    }
    static int compare(const char* s1, const char* s2, size_t n)
    {
        for (size_t i = 0; i < n; ++i)
        {
            if (!eq(s1[i], s2[i]))
            {
                return lt(s1[i], s2[i]) ? -1 : 1;
            }
        }
        return 0; // equal
    }
    static const char* find(const char* s, size_t n, const char& c)
    {
        for (size_t i = 0; i < n; ++i)
        {
            if (eq(s[i], c))
            {
                return &(s[i]);
            }
        }
        return nullptr;
    }
};

// define our own string type
using icstring = basic_string<char, ignorecases_traits>;

inline ostream& operator<<(ostream& os, const icstring& str)
{
    return os << string(str.data(), str.length());
}

int main(int argc, char const *argv[])
{
    icstring s1("hello");
    cout << boolalpha;
    cout << "s1 == HELLO: " << (s1 == "HELLO") << endl;
    cout << "find L in hello: " << s1.find("L");
    return 0;
}
