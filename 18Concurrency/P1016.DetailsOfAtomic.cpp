#include <iostream>
#include <thread>
#include <future>
#include <atomic>
#include <chrono>
#include <mutex>
using namespace std;

// details of atomic:
// template<tyepnaem T> struct atomic;
//      could be used in any types (built-in, compound, self-defined types)
//      specialization for bool, all intergers and pointer

// notice:
//      all operations get a copy(value), no one get reference
//      default constructor will initialize the atomic object completely (could be partial).
//          the only valid operation after a default constructor is atomic_init() to initialize it completely.
//      the constructor that accept a value of the corresponding type is not atomic.
//      all fucntion except constructors are overloaded as volatile and non-volatile version.

// operations:
//      atomic a = val // constructor is not atomic
//      atomic a; atomic_init(&a, val); // ditto
//      a.is_lock_free()
//      a.store(val)
//      a.load()
//      a.compare_exchange_strong(exp, des) // CAS operation
//      a.compare_exchange_weak(exp, des)   // weak CAS
//      a = val // assignment and reutrn copy of val
//      a.operator atomic()     // return copy of a
//  operations for intergers and pointers:
//      a.fetch_add(val)/a+=val
//      a.fetch_sub(val)/a-=val
//      ++a, a++, --a, a--
//  operations only for integers:
//      a.fetch_and(val) / a &= val
//      a.fetch_or(val) / a |= val
//      a.fetch_xor(val) / a ^= val

// notice:
//      oridinary assignment is delete (assign atomic to atomic)
//      but assignment of a inner type is provided, yields the passed argument

// CAS operation:
//      compare and swap operation
// persudo code:
/*
bool compare_exchange_strong(T& expected, T desired)
{
    if (this->load() == expected)
    {
        this->store(desired);
        return true;
    }
    else
    {
        expected = this->load;
        return false;
    }
}
*/
// weak version could be spuriously fail (expected == this->load() but also return false)'
// but more efficient than strong version.

// C-style atomic interfaces:
//      for code that need compatible between C and C++.
//      atomic_init, atomic_store, atomic_load, etc.
// C-style atomic types:
//      atomic_bool, atomic_char, atomic_int, atomic_size_ts, atomic_intptr_t, etc.

// sepcial atomic operations (global) for shared_ptr (atomic<shared_ptr<T>> is not available because shared_ptr is not copyable):
//      atomic_is_lock_free(&sp)
//      atomic_load(&sp)
//      atomic_store(&sp, sp2)
//      atomic_exchange(&sp, sp2)

int main(int argc, char const *argv[])
{
    
    return 0;
}
