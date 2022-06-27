#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <type_traits>
#include <iomanip>
using namespace std;


// print pair
template<typename T1, typename T2>
ostream& operator<<(ostream& os, std::pair<T1, T2> p)
{
    os << "[" << p.first << ", " << p.second << "]";
    return os;
}

// print hash table state
template<typename T>
void printHashTableState(const T& c)
{
    cout << "size: " << c.size() << endl;
    cout << "buckets: " << c.bucket_count() << endl;
    cout << "load factor: " << c.load_factor() << endl;
    cout << "max load factor: " << c.max_load_factor() << endl;
    if (typeid(typename iterator_traits<typename T::iterator>::iterator_category) == typeid(bidirectional_iterator_tag))
    {
        cout << "chaining style: doubly-linked" << endl;
    }
    else
    {
        cout << "chaing style: singly-linked" << endl;
    }

    // elements per bucket
    cout << "data: " << endl;
    for (auto idx = 0; idx < c.bucket_count(); ++idx)
    {
        cout << "b[" << setw(2) << idx << "]: ";
        for (auto iter = c.begin(idx); iter != c.end(idx); ++iter)
        {
            cout << *iter << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // unordered_set
    unordered_set<int> intset = {1, 2, 3, 5, 7, 11, 13, 17, 19};
    printHashTableState(intset);

    intset.max_load_factor(0.7);
    intset.insert({-7, 17, 33, 4});
    printHashTableState(intset);
    return 0;
}

