#include <iostream>
#include <iomanip>
using namespace std;

// std::ios_base:: iword/pword(save int/pointer) use a index in arry to identify a user-defined format flag
// it's allocated by std::ios_base::xalloc, every call of xalloc will get an unique index, so the index should be saved in a const value.

// if the flag is a pointer, then the resource allocation and dealloation should be concerned.
// the mechanism that manage flags of pointer type: 
// deep copy and destruction:
// std::ios_base::register_callback
// type of callback function: void(event e, ios_base& stream, int arg)
// event of callback: erase_event, imbue_event, copyfmt_event.

// no other details provided, read the manual.

static const int iword_index = std::ios_base::xalloc();

class Fraction
{
public:
    Fraction(int n = 1, int d = 1) : nume(n), denom(d) {}
    // consider polymorphism treat this as standard implementation of input and opuput of self-defined object
    template<typename charT, typename traits>
    void printOn(basic_ostream<charT, traits>& os) const
    {
        if (os.iword(iword_index))
        {
            os << nume << " / " << denom;
        }
        else
        {
            os << nume << "/" << denom;
        }
    }
private:
    int nume;
    int denom;
};

// user-defined manipulator that uses the user-defined flag
ostream& fraction_spaces(ostream& os)
{
    os.iword(iword_index) = true;
    return os;
}

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

int main(int argc, char const *argv[])
{
    cout << fraction_spaces << Fraction(1, 3) << endl;
    cout << iword_index << endl;
    return 0;
}
