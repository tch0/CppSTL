#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
using namespace std;

// std::array<T, N>, staticlly allocated array, just a wrapper of C array

int main(int argc, char const *argv[])
{
    array<int, 2> arr{1, 2};
    arr.front() = 100;
    // get C-style array inside
    arr.data()[1] = 10;
    copy(&arr[0], &arr[arr.size()], ostream_iterator<int>(cout, " "));

    // tuple interface of array
    cout << endl;
    cout << tuple_size<decltype(arr)>::value << endl;
    cout << get<1>(arr) << endl;

    return 0;
}
