#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <memory>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    // stateful lambda v.s stateful function object
    long sum = 0;
    vector<int> vec{1, 2, 3, 4};
    for_each(vec.begin(), vec.end(), [&sum](int val) -> void { sum += val; });
    cout << "sum of vec: " << sum << endl;

    // mutable lambda (capture local variables by value but not const, so you can modify them)
    // and two different do not shard their states

    // when states involved, lambda maybe not the best choice.
    return 0;
}