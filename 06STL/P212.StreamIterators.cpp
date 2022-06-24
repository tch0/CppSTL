#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// iterator adapters : inserter, stream iterators, reverse iterator, move iterators

int main(int argc, char const *argv[])
{
    vector<string> vec;
    copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(vec));
    sort(vec.begin(), vec.end());
    unique_copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "\n"));
    return 0;
}

// everything in this chapter is trivial, no need to record.