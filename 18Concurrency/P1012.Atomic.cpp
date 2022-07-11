#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <atomic> // for atomic types
#include <chrono>
using namespace std;

// problems that atomic should fix:
//      other thread could read a half-write value (need atomicity)
//      sequential consistency: execute as the order we coded, no unexpected instrcution reodering (no matter compiler optimization level, or hardware level?).

// the version that use atomic instead of codition_variable of P1003.ConditionVariable.cpp

// most important stuff of atomic:
//      load() : get current value from atomic
//      store() : set new value to atomic

// for the atomicity, some slight difference between atomic and normal type:
//      assignment operation return value instead of reference

// atomic object always should be initialized.
// if an atomic object was not been initilized in definition,
// the only next operation allowed is atomic_init(&atomic_var, init_val).
std::atomic<bool> readyFlag(false);

void thread1()
{
    // do something thread2 needs as preparation
    cout << "<return>" << endl;
    cin.get();
    readyFlag.store(true); // no lock needed for atomic.
}

void thread2()
{
    // wait until readyFlag is true (thread1 is done)
    while (!readyFlag.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    cout << "done" << endl;
}

class Foo
{
public:
    int x;
};

int main(int argc, char const *argv[])
{
    auto f1 = std::async(std::launch::async, thread1);
    auto f2 = std::async(std::launch::async, thread2);
    return 0;
}
