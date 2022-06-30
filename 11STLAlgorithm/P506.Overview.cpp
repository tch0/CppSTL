#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
using namespace std;

// classification:
// non-modifying algorithm
// modifying algorithm
// removing algorithm
// mutating algorithm
// sorting algorithm
// sorted-range algorithm
// numeric algorithm

template<typename C>
void printElements(const C& c)
{
    cout << "elements: ";
    copy(c.begin(), c.end(), ostream_iterator<decltype(*c.begin())>(cout, " "));
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // example:
    vector<int> vec(10);
    iota(vec.begin(), vec.end(), 10);
    printElements(vec);
    // exchange of relative value and abosolute value
    // adjacent_difference
    // partial_sum
    vector<int> res(10);
    partial_sum(vec.begin(), vec.end(), res.begin());
    printElements(res);
    adjacent_difference(res.begin(), res.end(), vec.begin());
    printElements(vec);
    return 0;
}
