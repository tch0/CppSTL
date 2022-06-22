#include <iostream>
#include <chrono>
#include <ratio>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// clock defines a epoch time and a tick unit
// a timepoint is either a positive or negative duration, relating to a certain clock.

// clock::duration : the duration type of the clock
// clock::rep : equivalent to clock::duration::rep
// clock::period : equivalent to clock::duration::period
// clock::time_point : timepoint type of the clock
// clock::is_steady : if the clock is steady
// clcok::now() : get a time_point of now time.

template<typename C>
void printClockData()
{
    using namespace std;
    cout << "- precision: ";
    using P = typename C::period; // time unit type
    if (ratio_less_equal<P, milli>::value)
    {
        // convert to and print as milliseconds
        using TT = typename ratio_multiply<P, kilo>::type;
        cout << fixed << double(TT::num) / TT::den << " milliseconds" << endl;
    }
    else
    {
        // print as seconds
        cout << fixed << double(P::num) / P::den << " seconds" << endl;
    }
    cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

template<typename TickType, intmax_t N, intmax_t D>
ostream& operator<<(ostream& os, const std::chrono::duration<TickType, ratio<N, D>>& d)
{
    os << "tick: " << d.count() << ", unit: " << ratio<N,D>::type::num << "/" << ratio<N,D>::type::den << " seconds";
    return os;
}

// overload for milliseconds
template<typename TickType>
ostream& operator<<(ostream& os, const std::chrono::duration<TickType, std::milli>& d)
{
    os << "duration: " << d.count() << " milliseconds";
    return os;
}

int main(int argc, char const *argv[])
{
    // get data of the clocks that STL supply
    cout << "system_clock: " << endl;
    printClockData<chrono::system_clock>();
    cout << endl << "high_resolution_clock: " << endl;
    printClockData<chrono::high_resolution_clock>();
    cout << endl << "steady_clock: " << endl;
    printClockData<chrono::steady_clock>();
    cout << endl;

    vector<int> vec;
    for (int i = 0; i < 100000; ++i)
    {
        vec.push_back(i);
    }
    random_shuffle(vec.begin(), vec.end());
    // record current time
    auto start = chrono::system_clock::now();
    // do some calculation
    sort(vec.begin(), vec.end());
    auto diff = chrono::system_clock::now() - start;
    auto sec = chrono::duration_cast<chrono::milliseconds>(diff);
    cout << sec << endl;
    return 0;
}
