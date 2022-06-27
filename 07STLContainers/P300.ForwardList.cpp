#include <iostream>
#include <forward_list>
#include <iterator>
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
    forward_list<int> fl = {1, 2, 3};
    cout << "fl.size: " << distance(fl.begin(), fl.end()) << endl; // O(N) complexity
    fl = {10, 100, 99};
    fl.sort();
    printElements(fl);

    fl.insert_after(fl.before_begin(), {1, 2, 3});
    printElements(fl);
    fl.push_front(1001);
    fl.insert_after(fl.begin(), {-1, -2, -3});
    printElements(fl);
    
    // insert {-10, -100} after the element -3
    auto posBefore = fl.before_begin();
    for (; next(posBefore) != fl.end(); ++posBefore)
    {
        if (*next(posBefore) == -3)
        {
            break;
        }
    }
    fl.insert_after(posBefore, {-10, -100});
    printElements(fl);
    fl.remove(1001);
    printElements(fl);

    forward_list<int> fl2 {1, 2, 3, 4};
    fl.splice_after(fl.begin(), fl2, fl2.begin(), fl2.end());
    printElements(fl);
    return 0;
}
