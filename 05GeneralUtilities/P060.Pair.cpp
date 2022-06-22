#include <utility> // for pair
#include <iostream>
#include <tuple> // for tuple, ignore
#include <functional> // for ref
using namespace std;

class Foo
{
    friend ostream& operator<<(ostream& os, const Foo& foo)
    {
        os << "a foo";
        return os;
    }
public:
    Foo(string, int) {}
};

class Bar
{
    friend ostream& operator<<(ostream& os, const Bar& bar)
    {
        os << "a bar";
        return os;
    }
public:
    Bar(int, double) {}
};

void f(pair<int, double> p)
{
    cout <<"f: " <<  p.first << ", " << p.second << endl;
}

int main(int argc, char const *argv[])
{
    // construct 
    pair<Foo, Bar> p(piecewise_construct, make_tuple<string, int>("hello", 10), make_tuple<int, double>(1, 2.0));
    cout << get<0>(p) << endl << get<1>(p) << endl;

    // arguments of make_pair will be decayed (array to pointer, function to function pointer)
    auto pp = make_pair("hello", 3.0); // type: pair<const char*, double>

    // after C++11
    f({1, 2.0});

    // use move semantic (no longer use foo and bar)
    Foo foo("hello", 10);
    Bar bar(1, 2.0);
    pair<Foo, Bar> p2 = make_pair(std::move(foo), std::move(bar));
    // use reference semantic, construct pair<int&, double&>
    int a = 1;
    double b = 2;
    auto p3 = make_pair(std::ref(a), std::ref(b));
    a = 10;
    b = 20;
    cout << p3.first << ", " << p3.second << endl; // 10, 20

    double c = 1.0;
    // extract second value into c, ignore first one
    std::tie(std::ignore, c) = p3; // result of std::tie is a tuple, p3.second is assigned to c
    cout << c << endl;

    // after C++11, tuple-like interface can be used on pair
    cout << tuple_size<decltype(p)>::value << endl; // 2
    tuple_element<0, decltype(p)>::type foo2("hello", 10); // type: foo
    cout << foo2 << endl;
    return 0;
}