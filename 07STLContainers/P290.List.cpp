#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

template<typename C>
void printElements(const C& c)
{
    cout << "elements: ";
    copy(c.begin(), c.end(), ostream_iterator<decltype(*c.begin())>(cout, " "));
    cout << endl;
}

int main(int argc, char const *argv[])
{
    list<int> l{1, 1, 2, 2, 3, 4, 4, 4, 5};
    l.unique();
    printElements(l);
    l.remove(2);
    printElements(l);
    list<int> l2{10, 100, 1000};
    l.splice(find(l.begin(), l.end(), 3), l2);
    printElements(l);

    l.sort();
    printElements(l);
    l2 = {1, 2, 3, 4, 5};
    l.merge(l2);
    printElements(l);
    printElements(l2);
    return 0;
}