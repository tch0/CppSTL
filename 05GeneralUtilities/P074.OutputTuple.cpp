#include <iostream>
#include <tuple>
using namespace std;

// a classic exercise: print tuple
// both class template recursion and function template overloading can do this

// 1: class template recursion
template<size_t IDX, size_t MAX, typename... Args>
struct PrintTuple
{
    static void print(ostream& os, const std::tuple<Args...>& t)
    {
        os << get<IDX>(t) << (IDX + 1 == MAX ? "" : ", ");
        PrintTuple<IDX+1, MAX, Args...>::print(os, t);
    }
};

// template partial specialization
template<size_t MAX, typename... Args>
struct PrintTuple<MAX, MAX, Args...>
{
    static void print(ostream& os, const tuple<Args...>& t)
    {
    }
};

template<typename... Args>
ostream& operator<<(ostream& os, tuple<Args...> t)
{
    os << "(";
    PrintTuple<0, sizeof...(Args), Args...>::print(os, t); // sizeof... for the size of tempalte paramter package
    return os << ")";
}

// 2: function tempalte overloading
template<size_t N> class uint {};

template<size_t IDX, size_t MAX, typename... Args>
void printTupleHelper(ostream& os, uint<IDX>, uint<MAX>, const std::tuple<Args...>& t)
{
    os << get<IDX>(t) << (IDX + 1 == MAX ? "" : ", ");
    printTupleHelper(os, uint<IDX+1>(), uint<MAX>(), t);
}

template<size_t MAX, typename... Args>
void printTupleHelper(ostream& os, uint<MAX>, uint<MAX>, const std::tuple<Args...>& t)
{
}

template<typename... Args>
ostream& printTuple(ostream& os, const std::tuple<Args...> t)
{
    // differ from operator<<
    os << "[";
    printTupleHelper(os, uint<0>(), uint<sizeof...(Args)>(), t);
    return os << "]";
}

int main(int argc, char const *argv[])
{
    cout << make_tuple(1, 2.0, make_tuple(10, 20, 30)) << endl;
    printTuple(cout, make_tuple(1, 2.0, "hello")) << endl;
    return 0;
}
