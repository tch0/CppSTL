#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <atomic>
using namespace std;

long num;
std::atomic<bool> readyFlag(false);

// the sequential consistency:
//      atomic has a guarantee for the instruction reordering.
//      in this example, it's certain the access of num will not execute before the load of readyFlag.
//          how?

void provider()
{
    // after reading a character
    cout << "<return>" << endl;
    cin.get();

    // provide some num
    num = 42;

    readyFlag.store(true);
}

void consumer()
{
    // wait for readiness and do something else
    while (!readyFlag.load())
    {
        cout.put('.').flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    // it's certain that reading of num is after writing num, so there is no need for a mutex to protect access of num.
    cout << "\n value: " << num << endl;
}


int main(int argc, char const *argv[])
{
    auto f1 = std::async(std::launch::async, provider);
    auto f2 = std::async(std::launch::async, consumer);
    return 0;
}
