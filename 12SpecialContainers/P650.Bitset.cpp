#include <iostream>
#include <bitset>
#include <functional>
#include <iterator>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char const *argv[])
{
    bitset<10> bs("1010"); // 0000001010, index from 9 to 0
    cout << bs << endl;
    cout << bs[1] << endl;
    cout << bs[9] << endl;

    // int and bitset conversion
    cout << bs.to_ullong() << endl;
    bs = 255;
    cout << bs << endl;
    return 0;
}
