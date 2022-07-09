#include <iostream>
#include <thread>
#include <future>
using namespace std;

// why multi-thread programs are so hard to write:
//      multi-thread programs will almost always accompany with concurrent data access.
//      It is rare for multiple threads to run unrelated to each other
//      so thread synchronization technology is necessary

// thread synchronization technology:
//      mutex and lock
//      condition variable
//      atomic

// problems that multi-thread programs will meet:
//      data race: always unexpcted, and concurrent data access may cause data race.
//              confliciting unsynchronized operations (like one write, another read) from multiple threads
//              at least one of them isn't atomic operation
//              these operations do not have an explicit/clear order.
//      lifetime problem:
//              using a global/static object, reference in other thread, may cause that visiting a non-exist/alrady-destruct object.

// to be more clearly, typical cases of data race:
//      unsynchronized data access: two threads read and write one same data, we don't exactly know who goes first who goes second.
//      half-written data: read a half-old/half-new data while another thread are modifying it.
//      reordered statement: due to the compiler optimization, reordered instructions may be work good for single-thread program,
//              but totally unexpected in multi-thread environment.

// the fetures we need to solve the concurrent data access problem:
//      atomicity: read/write a variable, execute a piece of code exclusively.
//      order: ensure the execute order of specific statements

// C++ Standard Library supply multiple methods to solve the problem:
//  from high-level to low-level:
//      using future and promise: always set shared state after set return value or an exception, reading must after writing is done.
//      using mutex and lock: to process critical section and protected zone.
//                  lock supplies atomicity
//      condition variable: let one thread wait for another thread supplies data and state that it needs, helpful to a definite order of multiple threads.
//      atomic data types: ensure that every visit on atomic variable or obejct is atomic.
//      low-level interfaces of atomic data types: manual barrier/fence

// high-level features are easy to use, lower risk.
// low-level features, have higher scalability, may supply a better performance, higher risk of being misused.

// By using atomicity, we could write lock-free code, but it's an area where experts occasionally make mistakes.
// Lock-free programming is even hard to experts, We can easily write lock-free code that seems to work, but it's hard to write
//      lock-free code that is correct and works well.

// volatile:
//  in C++, volatile is here to prevent over optimization, but it gives no guarantee of atomicity and a specific order.

int main(int argc, char const *argv[])
{
    
    return 0;
}
