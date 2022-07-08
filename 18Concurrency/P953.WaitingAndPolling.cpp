#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std;

// waiting a thread:
// interface of std::future<>:
// wait() : force the thread to start and wait it finish.
// wait_for() : wait the thread for a specific duration (do not force the thread to start if it's not starting now, like std::launch::deferred)
// wait_until() : wait the thread until a specific timepoint (ditto)

// return status: std::future_status
//      ready : the therad finished
//      timeout : the thread did not finish
//      deferred : the thread executed with std::launch::deferred strategy


// polling by pass a zero or negative duration to wait_for (or a passed timepoint to wait_until):
// to get the status of the thread but not actually wait it.

// this_thread::yield() :
//      hint to resschedule to next thread, to prevent one thread fills up the whole CPU.

// quick and dirty
// no meaning, just a example
int quickComputation()
{
    return 10;
}

// accurate but slow
int accurateComputation()
{
    int val = 0;
    for (int i = 0; i < 10000000; ++i)
    {
        val += i;
    }
    cout << "The accurate thead finished when the future destroy!" << endl;
    return val;
}

// usually f must be a global object, to prevent wait thread to terminate when the future destruct.
future<int> f;

int bestResultInTime()
{
    // define time slot (the least time we can afford) to get the answer
    auto tp = chrono::system_clock::now() + chrono::milliseconds(10); // 10ms
    // start both a quick and an accurate computation
    f = std::async(std::launch::async, accurateComputation);
    int guess = quickComputation();
    // give accurate computation the rest of time slot
    std::future_status s = f.wait_until(tp);
    if (s == std::future_status::ready)
    {
        return f.get();
    }
    else
    {
        return guess;
    }
}

int main(int argc, char const *argv[])
{
    cout << bestResultInTime() << endl;
    cout << boolalpha << f.valid() << endl;
    return 0;
}

