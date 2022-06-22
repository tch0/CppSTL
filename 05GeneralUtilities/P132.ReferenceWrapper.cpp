#include <iostream>
#include <functional>
#include <utility>
#include <vector>
using namespace std;

// reference_wrapper : just like reference in other languages, a variable reference(can change the objejct it point to)
// assignment will change the object it point to
// get() to get reference of current object324

template<typename T>
void foo(T t)
{
    cout << "foo: " << t << endl;
}

class Foo {};

int main(int argc, char const *argv[])
{
    int a = 0, b = 0;
    make_pair(ref(a), ref(b)) = make_pair(1, 2);
    cout << a << " " << b << endl;
    std::tie(a, b) = make_tuple(2, 3); // just like make_tuple(ref(a), ref(b)) = make_tuple(2, 3);
    cout << a << " " << b << endl;

    foo(a); // 2
    cout << a << endl; // 2
    foo(ref(a)); // 2
    cout << a << endl;

    vector<reference_wrapper<Foo>> vec;
    return 0;
}