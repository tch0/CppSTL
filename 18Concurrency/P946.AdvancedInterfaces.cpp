#include <iostream>
#include <future>
#include <thread>
#include <random>
#include <exception>
#include "ConcurrencyUtilities.h"
using namespace std;

// Concurrency support started from C++11.
// advanced interfaces of concurrency:
// std::async() : let a piece of functionality or callable object become an independent thread, run in background.
// std::future<> : allow us wait a thread to finish and get it's result (a return value or an exception).

int doSomething(char c)
{
    default_random_engine dre(c);
    uniform_int_distribution<int> id(10, 1000);
    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
    return c;
}

int func1()
{
    return doSomething('+');
}

int func2()
{
    return doSomething('-');
}

int main(int argc, char const *argv[])
{
    ElapsedTimeRecorder r("r");
    r.reset();
    cout << "starting func1 in background an func2() in forground: " << endl;
    std::future<int> result1(std::async(func1));
    int result2 = func2();
    int result = result1.get() + result2;
    cout << endl << "result of func1() + func2(): " << result << endl;
    r.showElapsedTime();
    return 0;
}