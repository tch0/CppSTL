#include <iostream>
#include <tuple>
#include <functional>
#include <utility>
#include <string>
#include <vector>
using namespace std;

void f(tuple<string, int, double> t)
{
    cout << "f: " << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
}

tuple<string, int, double> g()
{
    return {"yes", 1, 2.0};
}

int main(int argc, char const *argv[])
{
    // like pair: element of tuple could be reference
    string s;
    tuple<string&> t(s);
    s = "yes";
    cout << get<0>(t) << endl;
    // cout << get<2>(t) << endl; // compile-time error

    auto t2 = make_tuple(ref(s)); // tuye is tuple<string&>
    s = "no";
    cout << get<0>(t2) << endl;

    int a{};
    double b{};
    std::tie(a, b) = make_tuple(1, 2.0); // std::tie return a tuple<int&, double&>, do not use ref() in std::tie
    // std:tie(a, b) is just like std::make_tuple(std::ref(a), std::ref(b))
    cout << a << " " << b << endl;

    // initilizer list and tuple
    // after C++11 the constructor that use initilizer_list is explicit.
    // As a comparison, pair's constructor that use initilizer_list is not explicit(pair has exact number of members)
    // BUT: after C++14, the constructor of tuple changed to conditional explicit.(just like remove explicit, when one of the values in
    //      initilizer list can not implicitly convert to corresponding member of tuple, the constructor become explicit.)
    // but it's also passed when I compile on g++ with -std=c++11. so actully I'm not sure for the exact introducing time.
    tuple<string, int, double> t3{"hello", 1, 2.0}; // always valid
    tuple<string, int, double> t4 = {"hello", 1, 2.0};
    f({"hello", 1, 2});
    tuple<string> ts = "yes";
    vector<tuple<string, int>> v{{"yes", 1}, {"no", 0}};

    // other features of tuple: mostly for generic programming
    // get size and element type of tuple
    cout << tuple_size<decltype(ts)>::value << endl;
    tuple_element<1, decltype(t3)>::type i = 10;
    // concat multiple tuple into one: 
    auto tc = tuple_cat(t3, std::tie(i), make_tuple(10), make_pair(1, 2));
    cout << "size of tuple_cat rusult: " << tuple_size<decltype(tc)>::value << endl; // 7

    // interaction of pair and tuple: pair can be changed into tuple
    tuple<int, double> tp = make_pair(1, 2.0);
    tp = make_pair(2, 3.0);
    return 0;
}