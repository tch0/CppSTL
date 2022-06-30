#include <iostream>
#include <stack>
#include <functional>
#include <iterator>
#include <vector>
using namespace std;

// container adpater: stack, queue, priority_queue.

// stack: FILO

int main(int argc, char const *argv[])
{
    stack<int, vector<int>> s; // underlying data structure, default is deque.
    s.push(10);
    s.push(100);
    cout << "top: " << s.top() << endl;
    s.pop();
    cout << "top: " << s.top() << endl;
    return 0;
}
