#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <random>
using namespace std;

void doSomething(char c)
{
    default_random_engine dre;
    uniform_int_distribution<int> id(20, 50);
    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
}

int main(int argc, char const *argv[])
{
    cout << "starting two operations asynchronously: " << endl;
    auto f1 = async([]() { doSomething('+'); });
    auto f2 = async([]() { doSomething('-'); });
    
    // if at least one of the backgroud tasks is running, to prevent endless loop (in the case of both threads are deferred).
    if (f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
        f2.wait_for(chrono::seconds(0)) != future_status::deferred)
    {
        // poll until at least one of the loops finished
        while (f1.wait_for(chrono::seconds(0)) != future_status::ready &&
               f2.wait_for(chrono::seconds(0)) != future_status::ready)
        {
            this_thread::yield(); // hint to reshedule to the next thread
        }
    }
    cout << endl;
    // wait for all loops to be finished and process any exception
    try
    {
        f1.get();
        f2.get();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }
    cout << endl << "done" << endl;
    return 0;
}
