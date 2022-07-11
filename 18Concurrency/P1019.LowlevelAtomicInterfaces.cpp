#include <iostream>
#include <future>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;

// low-level atomic interfaces
// attention: low level atomic interfaces have no guarantee for sequential consistency
//            so it's tricky and dangerous.

// actually, when we called a.store(val), a.load(), it means a.store(val, std::memory_order_seq_cst), a.load(std::memory_order_seq_cst)
//      the default argument std::memory_order_seq_cst makes a guarantee of sequential consistency.
//  if we pass a std::memory_order_relaxed, will be no guratee of sequential consistency.
//      and that's called the low-level atomic interfaces.

// no other details here.
// read <C++ Concurrency in Action> 2nd edition for more info.
// it's for experts of concurrency.

int main(int argc, char const *argv[])
{
    
    return 0;
}
