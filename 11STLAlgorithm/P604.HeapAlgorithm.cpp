#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <iterator>
#include <numeric>
#include <string>
using namespace std;

// heap algorithms:
// make_heap
// push_heap
// pop_heap
// sort_heap

template<typename C>
void printElements(const C& c, const string& opStr = "")
{
    cout << opStr << " : ";
    copy(c.begin(), c.end(), ostream_iterator<decltype(*c.begin())>(cout, " "));
    cout << endl;
}

int main(int argc, char const *argv[])
{
    vector<int> vec(100);
    iota(vec.begin(), vec.end(), 0);

    // shuffle
    random_shuffle(vec.begin(), vec.end());
    printElements(vec, "after shuffle");

    make_heap(vec.begin(), vec.end());
    printElements(vec, "make_heap");

    vector<int> vec2(100);
    iota(vec2.begin(), vec2.end(), 100);
    copy(vec2.begin(), vec2.end(), back_inserter(vec));

    for (int i = 100; i <= vec.size(); ++i)
    {
        push_heap(vec.begin(), vec.begin() + i);
    }
    printElements(vec, "after push 100 to 199");
    sort_heap(vec.begin(), vec.end());
    printElements(vec, "after sort");
    return 0;
}
