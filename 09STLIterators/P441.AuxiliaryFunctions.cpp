#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

// void advance(pos, n) // will change iterator
// Iter next(pos)       // will not change iterator, but return a temporary iterator
// Iter next(pos, n)    // will not change iterator, but return a temporary iterator
// Iter prev(pos)       // will not change iterator, but return a temporary iterator
// Iter prev(pos)       // will not change iterator, but return a temporary iterator
// Dist distance(pos1, pos2)
// void iter_swap(pos1, pos2) // swap two values that the iterators point, might from different containers

template<typename C>
void printElements(const C& c)
{
    cout << "elements: ";
    copy(c.begin(), c.end(), ostream_iterator<decltype(*c.begin())>(cout, " "));
    cout << endl;
}

int main(int argc, char const *argv[])
{
    vector<int> vec {1, 2, 3};
    auto iter = vec.begin();
    advance(iter, 1);
    cout << *iter << endl;
    
    cout << *next(iter) << endl; // 3
    cout << *iter << endl; // 2

    cout << "distance: " << (next(iter) - vec.begin()) << endl;

    list<int> l {10, 100, 1000};
    iter_swap(vec.begin(), l.begin());
    printElements(vec);
    printElements(l);
    return 0;
}