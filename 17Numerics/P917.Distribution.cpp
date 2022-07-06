#include <iostream>
#include <random>
#include <iomanip>
#include <string>
#include <map>
using namespace std;

// random distribution:

template<typename Distr, typename Engine>
void PrintDistributionInfo(Distr d, Engine e, const string& name)
{
    cout << name << ": " << endl;
    cout << "- min(): " << d.min() << endl;
    cout << "- max(): " << d.max() << endl;
    cout << "-values: " << d(e) << " " << d(e) << " " << d(e) << " " << d(e) << endl;

    map<long long, int> valuecounter;
    for (int i = 0; i < 200000; ++i)
    {
        valuecounter[d(e)]++;
    }
    cout << "====" << endl;
    for (auto elem : valuecounter)
    {
        cout << setw(3) << elem.first << ": " << elem.second << endl;
    }
    cout << "====" << endl;
    cout << endl;
}

int main(int argc, char const *argv[])
{
    knuth_b e;

    uniform_real_distribution<> ud(0, 10);
    PrintDistributionInfo(ud, e, "uniform_distribution");

    normal_distribution<> nd;
    PrintDistributionInfo(nd, e, "normal_distribution");

    exponential_distribution<> ed;
    PrintDistributionInfo(ed, e, "exponential_distribution");

    gamma_distribution<> gd;
    PrintDistributionInfo(gd, e, "gamma_distribution");
    return 0;
}
