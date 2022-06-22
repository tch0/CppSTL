#include <iostream>
#include <memory> // for smart pointers
using namespace std;

class Foo
{
    friend ostream& operator<<(ostream& os, const Foo& foo)
    {
        cout << foo.str << endl;
        return os;
    }
public:
    Foo(string s = "hello") : str(s) {}
    ~Foo()
    {
        cout << "~Foo" << endl;
    }
private:
    string str;
};

int main(int argc, char const *argv[])
{
    // shared_ptr can manage memory that array new(new []) allocate but does not overload operator []
    shared_ptr<Foo> sp(new Foo[10], std::default_delete<Foo[]>());
    *(sp.get() + 1) = "no"s;
    cout << sp.get()[1] << endl;
    // cout << sp[1] << endl; // invalid
    sp.reset();

    cout << endl;
    // unique_ptr, template arguments could be Type[], use std::default_delete<Foo[]> to release memory
    // operator [] only for array partial specialization version
    // operator * and -> only for single object version
    unique_ptr<Foo[]> up(new Foo[10]);
    up[1] = "yes"s;
    cout << up[1] << endl;
    return 0;
}
