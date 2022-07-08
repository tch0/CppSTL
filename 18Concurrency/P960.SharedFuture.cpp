#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>
#include <chrono>
using namespace std;

// first get of future is valid, but second is UB (usually throw a std::future_error)

// if you want get the return value of a thread multiple times (like get result of one thread in multiple other threads)
//      use std::shared_future.

// std::future can be assigned to std::shared_future
// call std::future::share() will return a std::shared_future, so you can use auto in this case.

// if the thread throws an exception, every get() of shared_future will get this exception.

int queryNumber()
{
    cout << "read number: ";
    int num;
    cin >> num;
    if (!cin)
    {
        throw runtime_error("no number read");
    }
    return num;
}

void doSomething(char c, shared_future<int> f)
{
    try
    {
        int num = f.get();
        for (int i = 0; i < num; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(10));
            cout.put(c).flush();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception in thread " << this_thread::get_id() << ": " << e.what() << '\n';
    }
}

int main(int argc, char const *argv[])
{
    // call future::get twice
    try
    {
        auto f = []() -> int { return 1; };
        std::future<int> res = std::async(f);
        int a = res.get();
        int b = res.get();
    }
    catch(const std::future_error& e) // defined in <future>
    {
        std::cerr << "Exception: " << e.what() << '\n'; // std::future_error: No associated state
    }
    cout << endl;

    // shred_future
    try
    {
        // queryNumber only execute once, it's valid to call f.get() mutiple times.
        shared_future<int> f = async(queryNumber); // future assign to shared_future.
        auto f1 = async(launch::async, doSomething, '.', f);
        auto f2 = async(launch::async, doSomething, '+', f);
        auto f3 = async(launch::async, doSomething, '*', f);

        // wait for all loops to be finished
        f1.get();
        f2.get();
        f3.get();
        cout << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
