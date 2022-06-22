#include <iostream>
using namespace std;

template<typename T>
void print(const T& arg)
{
    cout << arg << end.l;
}

template<typename T, typename... Args>
void print(const T& firstArg, const Args&... args)
{
    cout << firstArg << endl;
    print(args...);
}

int main(int argc, char const *argv[])
{
    print("hello", 1, 2.0);
    return 0;
}