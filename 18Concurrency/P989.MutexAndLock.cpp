#include <iostream>
#include <thread>
#include <future>
#include <mutex>
using namespace std;

// mutex : mutual exclusion, control exclusive visit of a obejct.

// std::mutex
//      lock before visiting
//      unlock after visiting
//      no matter read or write.
// ensure exception-safe: using ARII:
//      std::lock_guard<std::mutex>, destrutor will call unlock.
// and avoid deadlock

// usually we do not use std::mutex directly, but use RAII class like std::lock_gurad<>

// other things:
//      std::recursive_mutex
//      std::mutex::try_lock, try to lock, no blocking if fail, but return a boolean.
//      std::timed_mutex/std::recursive_timed_mutex, try_lock_for, try_lock_until
//      std::adopt_lock:
//          pass to constructor of lock_guard or unique_ptr, manage a locked mutex.
//      process mutiple locks: std::lock
//          global function, lock multiple locks at same time, otherwise blocking.
//      std::try_lock global function:
//          try to lock multiple locks at same time, if fail, realease all locks that are already locked.
//          return -1 if success, if fail return the index of lock that fail to get.
//      class unique_lock<mutex_type>, more flexible than std::lock_guard, like unique_ptr
//          std::adopt_lock: manage a locked mutex
//          std::defer_lock: defer to lock, not lock at construction.
//          std::try_lock: try_lock at construction
//      std::once_flag and std::call_once, call a function only once.

// Have to say, it's hard to write multi-thread programs, especially the synchronization part.
// More real practices needed now!

// enable sychronized output of print
std::mutex printMutex;

void print(const std::string& s)
{
    std::lock_guard<std::mutex> l(printMutex); // RAII class
    for (char c : s)
    {
        cout.put(c);
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    auto f1 = std::async(std::launch::async, print, "Hello from a first thread");
    auto f2 = std::async(std::launch::async, print, "Hello from a second thread");
    print("Hello from the main thread");
    // there will be no interleaved output of three lines of output, but it's still not clear of the order of three print.
    return 0;
}
