#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <algorithm>
#include <map>
#include <numeric>
using namespace std;
using namespace std::placeholders;

// binders:
// bind(op, args...) // accepet a callable object
// mem_fn(op)   // convert member function pointer to a callable obejct
// not1(op) // !op(param)
// not2(op) // !op(param1, param2)

class Foo
{
public:
    void print()
    {
        cout << "void Foo::print()" << endl;
    }
    void printString(const string& str)
    {
        cout << "printString: " << str << endl;
    }
};

int main(int argc, char const *argv[])
{
    // bind : for all callable objects (include member function pointer)
    // normal function objects
    auto plus10 = bind(plus<int>(), _1, 10);
    cout << "1 + 10: " << plus10(1) << endl;
    // function composition
    auto plus10times2 = bind(multiplies<int>(), bind(plus<int>(), _1, 10), 2);
    cout << "(1+10)*2: " << plus10times2(1) << endl;
    auto pow3 = bind(multiplies<int>(), bind(multiplies<int>(), _1, _1), _1);
    cout << "10 ^ 3: " << pow3(10) << endl;
    // flip : invert the order of arguments
    auto flip2 = [](std::function<double(double, double)> func) -> std::function<double(double, double)> { return bind(func, _2, _1); };
    cout << "2 / 3 : " << flip2(divides<double>())(3, 2) << endl;
    // memeber function pointer
    auto printOfFoo = bind(&Foo::print, _1);
    printOfFoo(Foo());

    auto inc = [](int& i) -> int { return ++i; };
    // bind by reference
    int a = 1;
    bind(inc, a)();
    cout << "a after inc(pass by value): " << a << endl;
    bind(inc, ref(a))();
    cout << "a after inc(pass by reference): " << a << endl;

    cout << endl;
    // bind member function and pass pointer/smart pointer
    Foo foo;
    printOfFoo(&foo);
    auto sp = make_shared<Foo>();
    printOfFoo(sp);
    cout << endl;

    // bind data member pointer
    map<string, int> m {{"yes", 1}, {"no", 2}, {"hello", 10}};
    // type of binary op is: int(int, pair<const, string, int>)
    // bind(&map<string, int>::value_type::second, _2) equals to bind(&pair<const string, int>, _2)
    auto res = accumulate(m.begin(), m.end(), 0, bind(plus<int>(), _1, bind(&map<string, int>::value_type::second, _2))); // 
    // equivalent to
    auto res2 = accumulate(m.begin(), m.end(), 0, [](int init, const pair<string, int>& p) -> int { return init + p.second; });
    cout << "result of accumulation of value of map m (1): " << res << endl;
    cout << "result of accumulation of value of map m (2): " << res2 << endl;

    // mem_fn
    mem_fn(&Foo::print)(Foo());
    mem_fn(&Foo::printString)(Foo(), "yes");

    // not1, not2, almost deprecated.
    cout << boolalpha << not1(logical_not<bool>())(true) << endl;
    cout << not2(logical_or<bool>())(true, false) << endl; // !(true || false)
    return 0;
}