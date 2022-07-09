#include <iostream>
#include <future>
#include <thread>
using namespace std;

// details of std::async:
//      std::launch::async will always try to launch asynchronously, if it's unable to launch asynchronously, a system_error
//          will be thrown, if the reference counter of shared state decrease to 0 (usually when the future destruct), the thread will be finished (execute to it's end).
//      std::launch::deferred always defer the running of thread, until call wait() or get() of future, the task will be executed synchronously for sure.
//          if wait() and get() are not called eventually, the task will never be executed (even if the reference counter of shared object
//          decrease to 0/the future destruct).
//      std::launch::async | std::launch::deferred (or just do not pass the launch strategy) will try to launch::async first, if it's unable,
//          then launch::deferred, the behaviour is exactly same as the strategy it behave (but no system_error thrown in all cases).
//      do not use a 0 as launch strategy, it's UB.
//  usually we use the form of : future async(F func, args...)

// details of future:
//      manage a shared state which could be created by std::async, std::packaged_task, std::promise.
//      if the task realted to future defers (lanunch::deferred strategy), calling wait() or get() will start the task sychronously
//          but wait_for() and wait_until() will not.
//      future has a exclusive state: valid or invalid.
//          valid: before call get()
//          invalid: after call get()
//          call valid() to get the state, calling get() make the future invalid.
//          do not call get() of a invalid future (usually thrown a future_error).
//          for an invalid future, only move operations/destrcutor/valid() can be called.
//          default constructor will create a future with invalid state.
//      future is not copyable, but it's movable, so it's won't be that two futures share one shared state.
//      get()/wait()/wait_for()/wait_until() will block current thread until the related thread to be finished (call wait/get, regardless of synchronously or asynchronously)
//          or block for a specific time(wait_for/wait_until, if the thread is deferred, will do nothing).
//      share() create a shared_future, invlaidate current future, transfer control to shared_future.
//      call wait_for/wait_until to poll.

// details of shared_future:
//  just like future, but some differences:
//     - allow to call get() for multiple times, get() won't invalidate the state.
//          get() can be called multiple times from one shared_future, or multiple shared_future s(even in multiple thread) that share one shared state.
//          only first get() will block current thread and launch the task synchronously if the thread isn't finished.
//     - copyable
//     - the general version of get() is a const member and returns const T& (as a comparison, get() of future returns T, and it's non-const).
//          of course, the specilization of reference type and void returns T& and void, both are same.
//          so make sure the lifetime of returned const T& is shorter than the shared state.
//          always remember the returned reference is risky, suggest that do not bind it to a const T& but copy it to a new object.
//              Not to mention that it could be data races when multiple thread asynchronously read/write the one returned obejct.
//          the same problem happens to exception obejct, if catched by reference, it could be data race too. 
//              only catching by T& and modifying exception cause the problem, all catching by const T& wil not.
//              suggest use current_exception() and rethrow_exception(), they will copy the exception, but copy is expensive.
//              so make your own trade-off.
//        !!! notice: Make sure you know exactly what you are doing when you use a non-const reference(even const reference) of returned value and catched exception.
//     - do not supply share().

// details of promise:
//      hold a result or an exception (s shared state)
//      get_future to get a future obejct (if there is no shared state, will throw std::future_error)
//      get_future can be called only once, the second call will throw std::future_error.
//      set_value/set_exception/... are thread-safe.
//      not copyable, but movable.

// details of packaged_task:
//      get_future to get a future obejct (if there is no shared state, will throw std::future_error)
//      get_future can be called only once, the second call will throw std::future_error.
//      first call task() will start the task (typically in a seperate thread)
//      second call task will throw a future_error.
//      destructor and reset() will release the shared state(if it's not ready, make it ready, and store a future_error as result).
//      make_ready_at_thread_exit() to make sure shared state be ready when thread exit.
//      not copyable, but movable.

// details of thread:
//      to represent and start a thread
//      relate to a callable object and possible arguments
//      either a join (wait result from thread) and a detach (lost connection of thread) should be call before the thread object destruct,
//          otherwise std::terminate will be called when the thread object destruct.
//      if thread object is related to a thread, we call it joinable, in this case, joinable() will return true, get_id() will get the thread ID.
//          if not, get_id() will return a non-thread ID which is equal to std::thread::id(), and detach()/join() will throw a system_error.
//      not copyable, but movable.
//      notice:
//          detached thread should not visit an oebject that already destruct. this means when our program being finished, there should not be a detached
//              thread still visiting global/static obejct (either finish it early or do not visit global/static object).
//      static function hardware_concurrency() returns a possible max thread number, not ensure to be accurete, treat it as a reference value.
//          if the number is not computable or unclear, return 0.

// namespace this_thread:
//  global functions:
//      get_id(): ID of current thread
//      sleep_for(dur): block current thread for a specific duration
//      sleep_until(tp): block current thread until a specific timepoint
//      yield(): hint to release CPU and reschedule to next thread. 
//          typical application scenarios: a loop waiting or polling another thread to do something(get ready for the data, release a lock, etc.)

int main(int argc, char const *argv[])
{
    cout << std::thread::hardware_concurrency() << endl; // 8 in my machine
    return 0;
}
