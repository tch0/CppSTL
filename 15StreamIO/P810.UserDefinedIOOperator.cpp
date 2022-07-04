#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class Fraction
{
public:
    Fraction(int n = 1, int d = 1) : nume(n), denom(d) {}
    // consider polymorphism treat this as standard implementation of input and opuput of self-defined object
    template<typename charT, typename traits>
    void printOn(basic_ostream<charT, traits>& os) const
    {
        os << nume << "/" << denom;
    }
    template<typename charT, typename traits>
    void scanFrom(basic_istream<charT, traits>& is)
    {
        int n, d;
        is >> n;
        is.ignore();
        is >> d;
        if (is)
        {
            nume = n;
            denom = d;
        }
    }
private:
    int nume;
    int denom;
};

// generic operator<< (for all kinds of ostream)
// also cancel the effect of last setw
// but it's not in namespace std, so it can not be found through ADL(Argument-dependent lookup).
template<typename charT, typename traits>
std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, const Fraction& f)
{
    // string stream with same format without special field with
    std::basic_ostringstream<charT, traits> s;
    s.copyfmt(os);
    s.width(0);
    f.printOn(s); // dispatch print action to member function of Fraction
    os << s.str(); // print string to ostream, last setw(set field width) will only affect this write action.
    return os;
}

// generic operator>>
template<typename charT, typename traits>
std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& is, Fraction& f)
{
    f.scanFrom(is);
    return is;
}

int main(int argc, char const *argv[])
{
    cout << setw(10) << Fraction(1, 10) << endl;
    Fraction f;
    cin >> f;
    cout << f << endl;
    return 0;
}
