#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable> // for 
using namespace std;

// the method that let one thread wait for another:
//      waiting and polling
//  example:
/*
bool readyFlag;
std::mutex readyFlagMutex;
{
    std::unique_lock<std::mutex> ul(readyFlagMutex);
    while (!readyFlag)
    {
        ul.unlock();
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ul.lock();
    }
}
*/

// a better way to do this: using condition variable
//      by using it, a thread can wake up other one or more waiting threads.

// how to use condition variable:
//      include <mutex> and <condition_variable> 
//      declare a mutex and a condition variable
//          std::mutex radyMutex;
//          std::condition_variable redyCondVar;
//      in the thread that condition fulfill:
//          readyCondVar.notify_one()
//          readyCondvar.notify_all()
//      in the thread that is waiting for the condition fufill:
//          std::unique_lock<std::mutex> l(readyMutex);  // must be unique_lock, can not be lock_gurad, because readyCondVar.wait(l) will unlock and lock l.
//          readyCondVar.wait(l);

// spurious wakeup:
//      even if the condition do not notify, the wait of condition variable may return
//      in these cases, we should do a second check of whether the condition is fulfilled.
//          in practice, pass a lambda condition_variable.wait to do this.

bool readyFlag;
std::mutex readyMutex; // for exclusive visiting of readyFlag
std::condition_variable readyCondVar; // waiting for readyFlag to become true

void thread1()
{
    // do something thread2 needs as preparation
    cout << "<return>" << endl;
    cin.get();
    // signal that thread1 has prepared a condition
    {
        std::lock_guard<std::mutex> lg(readyMutex);
        readyFlag = true;
    }
    readyCondVar.notify_one(); // the condition is fulfilled, then notify the threads that wait for the condition.
}

void thread2()
{
    // wait until thread1 is ready (readyFlag is true)
    {
        std::unique_lock<std::mutex> ul(readyMutex);
        readyCondVar.wait(ul, []{ return readyFlag; }); // lambda is for second check whether the condition is fulfilled (for the cases of spurious wakeup).
        // wait will call the second argument(the function object) continuously
    }
    cout << "done" << endl;
}

int main(int argc, char const *argv[])
{
    auto f1 = std::async(std::launch::async, thread1);
    auto f2 = std::async(std::launch::async, thread2);
    return 0;
}
