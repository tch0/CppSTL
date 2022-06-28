#include <iostream>
#include <iterator>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

// reverse iterator: must be bidirectional iterator
// insert iterator(aka inserter): back, front, general
// stream iterator: istream/ostream iterator
// move iterator: move elements instead of copy, input normal iterator, output move iterator
//                must make sure the elements are processed only once.
//                move() function in algorithm will do the same thing.
template<typename C>
void printElements(const string& str, const C& c)
{
    cout << str;
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // reverse iterator
    vector<int> vec {1, 2, 3, 4, 5};
    auto pos = find(vec.begin(), vec.end(), 4);
    vector<int>::reverse_iterator rpos(pos);
    cout << *pos << endl;
    cout << *rpos << endl; // 3
    cout << *rpos.base() << endl; // 4, that is the value iterator pos point
    for (auto iter = vec.rbegin(); iter != vec.rend(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
    // rbegin() is reverse_iterator(end())
    // rend() is reverse_iterator(begin())

    // inserter: back_insert_iterator, front_insert_iterator, insert_iterator.
    vec = {1, 2, 3, 4};
    vec.reserve(vec.size() * 2);
    copy(vec.begin(), vec.end(), back_inserter(vec));
    printElements("vec: ", vec);

    // ostream iterator
    cout << "ostream_iterator: ";
    copy(vec.begin(), vec.end(), ostream_iterator<decltype(vec)::value_type>(cout, "="));
    cout << endl;

    // istream iterator
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec));
    cout << "elements before and input: ";
    copy(vec.begin(), vec.end(), ostream_iterator<decltype(vec)::value_type>(cout, " . ")); // Ctrl + Z for EOF
    cout << endl;

    // move iterators
    vector<string> vecs {"hello", "world"};
    vector<string> vecs2(make_move_iterator(vecs.begin()), make_move_iterator(vecs.end()));
    cout << "vecs: ";
    copy(vecs.begin(), vecs.end(), ostream_iterator<string>(cout, "-"));
    cout << endl << "vecs2: ";
    copy(vecs2.begin(), vecs2.end(), ostream_iterator<string>(cout, "-"));
    cout << endl;

    copy(make_move_iterator(vecs2.begin()), make_move_iterator(vecs2.end()), vecs.begin());
    printElements("vecs after: ", vecs);
    printElements("vecs2 after: ", vecs2);
    return 0;
}