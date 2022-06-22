#include <memory>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    try
    {
        shared_ptr<string> sp(new string("hi"));
        weak_ptr<string> wp(sp);
        sp.reset();
        cout << wp.use_count() << endl; // 0
        cout << boolalpha << wp.expired() << endl; // true
        shared_ptr<string> p(wp); // throw std::bad_weak_ptr
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl; // bad_weak_ptr
    }
    return 0;
}
