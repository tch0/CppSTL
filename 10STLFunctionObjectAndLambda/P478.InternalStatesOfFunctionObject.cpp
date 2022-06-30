#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

// get result or feedback from a function object
// 1. let function object hold a outter object as state, read state outside
// 2. pass function by reference (explicitly pass the template argument as reference)
// 3. use the result of for_each -- the return value is the final function obejct.(only for_each has this feature)

class MeanValue
{
private:
    double num;
    double sum;
public:
    MeanValue() : num(0), sum(0) {}
    void operator()(int elem)
    {
        ++num;
        sum += elem;
    }
    double value()
    {
        return sum / num;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> vec {1, 2, 3, 100};

    // pass function obejct as reference
    MeanValue mvr;
    for_each<decltype(vec.begin()), MeanValue&>(vec.begin(), vec.end(), mvr);
    cout << "average value: " << mvr.value() << endl;

    // use return value of for_each
    auto mv = for_each(vec.begin(), vec.end(), MeanValue());
    cout << "average value: " << mv.value() << endl;
    return 0;
}
