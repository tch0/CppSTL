#include <iostream>
#include <future>
#include <thread>
#include <random>
#include <exception>
#include <list>
#include "ConcurrencyUtilities.h"
using namespace std;

// Concurrency support started from C++11.
// advanced interfaces of concurrency:
// std::async() : let a piece of functionality or callable object become an independent thread, run in background.
// std::future<> : allow us wait a thread to finish and get it's result (a return value or an exception).

// The future object which receive result that async returns is important, it makes sure the thread will start when we uses the future object.
//      even if the return type is a void or we do not interest in the result, we must hold it.

// in order to get most efficiently parallelism, async() shoule be [call early and return late] as much as possible.

// tell async() to start the thread asynchronously now by pass a launch strategy:
//      std::future<> result = std::async(std::launch::async, func)
//  if aynchronous start can not execute, will throw a system_error.
//      after doing this, get() is no longer needed.
//  but using get() will make logic more clear.
//  if the result is not assigned to a future, func will be executed synchronously (executed before the future object detructed).
//  On the contrary, std::launch::deferred will force a deferred execution, func will not be executed until call get.

// exception handling:
// if a thread that std::async start throw an exception, it will be thrown to host thread when we call get().

int doSomething(char c)
{
    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(50));
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
    // multi-thread version
    r.reset();
    cout << "starting func1() in background an func2() in forground: " << endl;
    std::future<int> result1(std::async(func1));
    int result2 = func2();
    int result = result1.get() + result2;
    cout << endl << "result of func1() + func2(): " << result << endl;
    r.showElapsedTime();

    cout << endl;
    // as a comparison, a single thread version
    r.reset();
    cout << "starting func1() and func2() in one thread: " << endl;
    int res = func1() + func2();
    cout << endl << "result of func1() + func2(): " << res << endl;
    r.showElapsedTime();

    // start func1 right now, but don't catch the result, will execute synchronously
    cout << endl;
    r.reset();
    cout << endl << "starting func1 in backgroud, but synchrnously: " << endl;
    auto f = std::async(std::launch::async, func1);
    int res2 = func2();
    r.showElapsedTime();
    
    cout << endl;
    r.reset();
    // exception handling
    auto func = []() -> void {
        throw runtime_error("Exception throwed in func thread");
    };

    auto f1 = std::async(func);
    cin.get(); // like getchar();
    cout << "wait for the endless task return: " << endl;
    try
    {
        f1.get(); // wait func throw an exception
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}