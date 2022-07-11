#include <iostream>
#include <future>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>
using namespace std;

// implementation of multi-thread queue

// the predicate that pass to condition_variable::wait is always called when mutex is locked,
//      so it's always safe in the lambda to process the protected object by mutex.

// steps of waiting function of condition_variable:
// 1. unlocking mutex and enter waiting state
// 2. waiting state: unblocking the wait
//          typically this_thread::yield() then this_thread::sleep_for()
// 3. relocking the mutex

std::queue<int> q;
std::mutex queueMutex;
std::condition_variable queueCondVar;

void provider(int val)
{
    for (int i = 0; i < 6; ++i)
    {
        {
            std::lock_guard<std::mutex> lg(queueMutex);
            q.push(val + i);
        } // release lock
        queueCondVar.notify_one();
        // only wakeup one waiting thread (it's not sepcified that which one will be waken up)
        // if multiple consumers must process same datas, could use notify_all().
        std::this_thread::sleep_for(std::chrono::milliseconds(val));
    }
}

void consumer(int num)
{
    while (true)
    {
        int val;
        {
            std::unique_lock<std::mutex> ul(queueMutex);
            queueCondVar.wait(ul, [] { return !q.empty(); });
            val = q.front();
            q.pop();
        } // release lock
        cout << "consumer " << num << ": " << val << endl;
    }
}

int main(int argc, char const *argv[])
{
    // three providers values 100+, 300+, and 500+
    auto p1 = std::async(std::launch::async, provider, 100);
    auto p2 = std::async(std::launch::async, provider, 300);
    auto p3 = std::async(std::launch::async, provider, 500);

    // starting two comsumers printing the values
    auto c1 = std::async(std::launch::async, consumer, 1);
    auto c2 = std::async(std::launch::async, consumer, 2);
    return 0;
}
