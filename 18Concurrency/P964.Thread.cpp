#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>
#include <random>
using namespace std;

// high-level intefaces: std::async, std::future(shard_future).

// low-level interfaces: std::thread, std::promise

// std::thread:
// difference between std::async:
//      no launch policy, always try to start target function to a new thread immediately, if failed, will throw a system_error
//      no interfaces to process the result of thread.
//      if a thread throws an exception but not catched, will call terminate immediately.
//      if you want wait it to be finished, or let it run in background, must declare explicitly. (use join or detach.)
//          if you did not call join or detach before it's destruction or move assignment, in that moment, std::terminate will be called.
//      if a thread run on background, but main is finished, other threads will be terminated.

// almost nobody need a detached thread. 

// thread id:
// type: std::thread::id
// get thread id: 
//      this_thread::get_id()  // this_thread is a nemespace
//      thread::get_id()       // thread is an object
// no thread id: std::thread::id() // default constructor

// the only way to identify a thread is compare it's thread id.
// A finished thread id may be reused by system.

void doSomething(int num, char c)
{
    try
    {
        default_random_engine dre;
        uniform_int_distribution<int> id(100, 1000);
        for (int i = 0; i < num; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(id(dre)));
            cout.put(c).flush();
        }
    }
    catch(const std::exception& e)
    {
        cerr << "THREAD-EXCEPTION (thread " << this_thread::get_id() << "): " << e.what() << endl;
    }
    catch(...)
    {
        cerr << "THREAD-EXCEPTION (thread " << this_thread::get_id() << ")" << endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        thread t1(doSomething, 5, '.');
        cout << "- started fg thread " << t1.get_id() << endl;

        for (int i = 0; i < 5; ++i)
        {
            thread t(doSomething, 10, 'a' + i);
            cout << "- detach started bg thread " << t.get_id() << endl;
            t.detach();
        }
        cin.get();
        cout << "- join fg thread " << t1.get_id() << endl;
        t1.join();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }
    cout << endl;
    return 0;
}
