#include <iostream>
#include <deque>
#include <vector>
#include <queue> // for priority_queue
#include <functional>
#include <algorithm>
#include <numeric>
using namespace std;

// priority queue
// in practice, maybe make_heap/pop_heap/push_heap/sort_heap is enough to use

// implement a priority queue through heap algorithms from <algorithm>
template<typename T, typename Container = vector<T>, typename Compare = std::less<typename Container::value_type>>
class PriorityQueue
{
private:
    Compare comp;
    Container c;
public:
    using value_type = typename Container::value_type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = typename Container::size_type;
    using container_type = Container;
    using value_compare = Compare;
    explicit PriorityQueue(const Compare& cmp = Compare(), const Container& cont = Container())
        : comp(cmp), c(cont)
    {
        make_heap(c.begin(), c.end(), comp);
    }
    explicit PriorityQueue(const Compare& cmp, Container&& cont)
        : comp(cmp), c(std::move(cont))
    {
        make_heap(c.begin(), c.end(), comp);
    }
    void push(const value_type& elem)
    {
        c.push_back(elem);
        push_heap(c.begin(), c.end(), comp);
    }
    const value_type& top() const
    {
        return c.front();
    }
    void pop()
    {
        pop_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }
    bool empty() const
    {
        return c.empty();
    }
    size_type size() const
    {
        return c.size();
    }
};

int main(int argc, char const *argv[])
{
    vector<int> vec(100);
    iota(vec.begin(), vec.end(), 1);
    random_shuffle(vec.begin(), vec.end());

    // heap sort
    PriorityQueue<int> pq(less<int>(), std::move(vec)); // no longer use vec
    // priority_queue : will be same result
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    return 0;
}