#include <iostream>
#include <iterator>
#include <forward_list>
#include <list>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
using namespace std;

// iterator tag:
/*
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };
*/
// details of iterator_traits
/*
typedef typename T::iterator_category iterator_category;
typedef typename T::value_type        value_type;
typedef typename T::difference_type   difference_type;
typedef typename T::pointer           pointer;
typedef typename T::reference         reference;
*/

inline void printSepcificIteratorCategory(const input_iterator_tag& category)
{
    cout << "input iterator";
}

inline void printSepcificIteratorCategory(const output_iterator_tag& category)
{
    cout << "output iterator";
}

inline void printSepcificIteratorCategory(const forward_iterator_tag& category)
{
    cout << "forward iterator";
}

inline void printSepcificIteratorCategory(const bidirectional_iterator_tag& category)
{
    cout << "bidirectional iterator";
}

inline void printSepcificIteratorCategory(const random_access_iterator_tag& category)
{
    cout << "random-access iterator";
}

template<typename C>
void printIteratorCategory(const string& str, const C& c)
{
    cout << setw(20) << left << str << ": ";
    printSepcificIteratorCategory(typename iterator_traits<decltype(begin(c))>::iterator_category());
    cout << endl;
}

int main(int argc, char const *argv[])
{
    printIteratorCategory("vector", vector<int>());
    printIteratorCategory("list", list<int>());
    printIteratorCategory("deque", deque<int>());
    printIteratorCategory("forward_list", forward_list<int>());
    printIteratorCategory("array", array<int, 10>());
    int arr[] = {1, 2};
    printIteratorCategory("C array", arr);

    printIteratorCategory("set", set<int>());
    printIteratorCategory("map", map<int, string>());
    printIteratorCategory("unordered_map", unordered_map<int, string>());
    printIteratorCategory("unordered_set", unordered_set<int>());
    printIteratorCategory("string", string());

    cout << setw(20) << left << "ostream_iterator" << ": ";
    printSepcificIteratorCategory(iterator_traits<ostream_iterator<int>>::iterator_category());
    cout << endl;
    return 0;
}
