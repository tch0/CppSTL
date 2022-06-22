#include <iostream>
#include <type_traits>
#include <memory>
using namespace std;

// type traits: supply a method that handle property of a type.
//              it's a template and can generate a type or a value according to template arguments in compile-time.

class Foo {};
enum class Bar {};

class DFoo : public Foo {};


int main(int argc, char const *argv[])
{
    cout << boolalpha;
    // type predicate
    cout << is_void<void>::value << endl;
    cout << is_floating_point<long double>::value << endl;
    cout << is_arithmetic<unsigned long>::value << endl;
    cout << is_signed<int>::value << endl;
    cout << is_unsigned<unsigned long long>::value << endl;
    int a;
    cout << is_rvalue_reference<decltype(std::move(a))>::value << endl;
    // cout << is_bounded_array<int[10]>::value << endl; // C++20 not support in MinGW64 yet
    // cout << is_scoped_enum<Bar>::value << endl; // C++23 not supported yet

    // traits for class details
    cout << endl;
    cout << is_polymorphic<Foo>::value << endl; // false
    cout << is_trivial<Foo>::value << endl; // true
    cout << is_trivially_move_assignable<Foo>::value << endl; // true
    cout << is_nothrow_copy_constructible<Foo>::value << endl; // true

    // traits for type relations
    cout << endl;
    cout << is_same<int, signed int>::value << endl; // true
    cout << is_base_of<Foo, DFoo>::value << endl; // true
    cout << is_convertible<int, double>::value << endl; // true
    cout << is_trivially_constructible<double, int>::value << endl; // false

    // type modifier: const/volatile, reference(l&r), pointer, signed/unsigned, array extents
    add_const<int>::type c = 10; // const int c = 10;
    add_rvalue_reference<int>::type r = 10; // int&& r = 10;
    add_lvalue_reference<decltype(c)>::type rc = c; // const int& rc = c;
    remove_pointer<int*>::type d = 10; // int d = 10;
    remove_all_extents<int[10][11]>::type e = 10; // int e = 10;

    // other traits
    cout << endl;
    cout << rank<int[10][1]>::value << endl; // 2
    decay<int[10]>::type p = new int[10]; // int* p = 10; // decay: array to pointer, function to function pointer, lvalue to rvalue(remove cv)
    delete p;
    return 0;
}
