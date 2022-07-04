#include <iostream>
#include <iomanip> // for manipulators
#include <limits>
#include <functional>
using namespace std;

// basic I/O manipulators in <iostream>: endl/ends/flush/ws

// classification of manipulators:
// fmtflags: (no)boolalpha, (no)showbase, (no)showpoint, (no)showpos, (no)skipws, (no)upppercase, (no)unitbuf.
// adjustfield: left, right, internal
// basefield: dec, hex, oct
// floatfield: fixed, scientific, hexfloat, defualtfloat.
// basic_istream manipulators: ws
// basic_ostream manipulators: endl, ends, flush, ...

// no-argument manipulators are functions whose siginature is ostream&(ostream&)
//      operator<< that receive a ostream&(ostream&) will call the passing function with the ostream object.
//      cout << endl is euqivalent to endl(cout).
// manipulators with arguments usually implement as a function(or a class), the function will return a specific object,
//      and operator<< will being overloaded for these obejcts.

// user-defined manipulator:

// no-arguments manipulator: usually defined as a ostream&(ostream&) function
// the manipulator that ignore one line of input.
template<typename charT, typename traits>
inline std::basic_istream<charT, traits>& ignoreLine(std::basic_istream<charT, traits>& is)
{
    // skip until end-of-line
    is.ignore(std::numeric_limits<std::streamsize>::max(), is.widen('\n'));
    return is;
}

// manipulator that accept arguments: multiple methods to implement, the standard do not restrict.
//     1. defined as an object, overload operator<<(whatever the manipulator call a isolate function or a constructor).
//     2. I think, maybe..., return a function object(with the signature ostream&(ostream&)) and overload<< that accept std::fucntion

// method 1: the easiest and intuitive way.
class PrintNAsterisk // just for test, no practical meaning
{
private:
    int num;
public:
    explicit PrintNAsterisk(int n = 1) : num(n)
    {
    }
    template<typename charT, typename traits>
    friend std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, const PrintNAsterisk& obj)
    {
        for (int i = 0; i < obj.num; ++i)
        {
            cout << "*";
        }
        return os;
    }
};

// method 2: return a function object, and overload operator<< for std::function
// ===== just for fun, show the possibility, not for practice. =====

// It won't work if both operator<< and PrintNUndersocre::operator() are templates,
// in that case, we need an explicit cast to std::function for manipulator object.

// template<typename charT, typename traits>
// inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os,
//     const std::function<std::basic_ostream<charT, traits>&(std::basic_ostream<charT, traits>&)>& func)
// {
//     func(os);
//     return os;
// }

ostream& operator<<(ostream& os, const std::function<ostream&(ostream&)>& func)
{
    func(os);
    return os;
}

class PrintNUndersocre
{
private:
    int num;
public:
    PrintNUndersocre(int n = 1) : num(n)
    {
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& operator()(std::basic_ostream<charT, traits>& os)
    {
        for (int i = 0; i < num; ++i)
        {
            cout << "_";
        }
        return os;
    }
};

int main(int argc, char const *argv[])
{
    cout << setw(10) << left << setfill('_') << showpos;
    cout << 10;
    endl(cout); // equal to cout << endl
    cout << "next" << endl;

    int a;
    cin >> ignoreLine >> a; // will ignore the first line of input
    cout << a << endl;
    cout << PrintNUndersocre(20) << endl;
    return 0;
}
