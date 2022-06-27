#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vec{1, 2, 3, 4};
    vec.reserve(100);
    cout << vec.capacity() << endl;
    vec.shrink_to_fit();
    cout << vec.capacity() << endl;
    cout << vec.max_size() << endl;
    return 0;
}
