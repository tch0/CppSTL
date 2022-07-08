#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>
using namespace std;

// std::promise in <future>:
// used to transfer result and exception from detached thread to main thread:
// need pass to thread by reference, and call set_value or set_exception in detached thread.

// get the result from a promise need with the help of std::future (initilize future with the promise.get_future())
// call std::future::get will block the main thread, and run the detached thread until set_value or set_exception called
// notice: not wait until the detached thread to be finished.
//         if you want to wait until the detached thread to be finished, call set_value_at_thread_exit()/set_exception_at_thread_exit().

// std::promise and std::future are not here for multi-thread programs only.
// It's feasible for promise to store a result or an exception and process it later with a future in single-thread environment.

void doSomething(std::promise<string>& p)
{
    try
    {
        // read character and throw exception if 'x'
        cout << "read char ('x' for exception): ";
        char c = cin.get();
        if (c == 'x')
        {
            throw runtime_error("char 'x' read");
        }
        string s = string("char ") + c + " read";
        // store result
        p.set_value(std::move(s));
        // p.set_value_at_thread_exit(std::move(s));
    }
    catch(...)
    {
        // store exception
        p.set_exception(std::current_exception());
        // p.set_exception_at_thread_exit(std::current_exception());
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        // using a promise to store the outcome
        std::promise<string> p;
        std::thread t(doSomething, std::ref(p)); // promise should be passed only by reference, not by value
        t.detach();

        // create a future to process the outcome
        std::future<string> f(p.get_future());
        cout << "result: " << f.get() << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Exception" << std::endl;
    }
    return 0;
}
