#include <iostream>
#include <chrono>
using namespace std;

// all in namespace std::chrono
// 3 important concepts: 
//      duration : type std::chrono::duration
//          means a period of time, include a tick count(numeric type) and a time unit(a ratio, the unit of the ratio is second)
//      timepoint:
//          the combination of a duration and a epoch time(a start time of the duration, typically unix epoch time: 1970.1.1 00:00 UTC+0)
//      clock:
//          an object that define the epoch time, different clock has different epoch time.
//          it must use same epoch/clock for handling two timepoint.

// pre-defined duration types that use integer type: in std::chrono
// nanoseconds, microseconds, milliseconds, seconds, minutes, hours
// C++20: days, weeks, months, years

// arithmetic operations for duration: can be different template arguments
// +-*/ of two durations
// +- tick, +- durations
// compare two durations

// count() for tick count
// duration::rep for tick type
// duration::period for unit type
// duration_cast<D>(d) : explicitly cast

template<typename TickType, intmax_t N, intmax_t D>
ostream& operator<<(ostream& os, const std::chrono::duration<TickType, ratio<N, D>>& d)
{
    os << "tick: " << d.count() << ", unit: " << ratio<N,D>::type::num << "/" << ratio<N,D>::type::den << " seconds";
    return os;
}

int main(int argc, char const *argv[])
{
    chrono::duration<int> oneSec(1); // unit is second
    chrono::duration<double, ratio<60>> sixMin(6); // unit is 60 second(aka minutes)
    chrono::duration<long, ratio<1, 1000>> fiveMilliSec(5); // unit is 1/1000 second(1 millisecond).
    
    // pre-defined duration types
    chrono::hours tenHours(10);
    cout << tenHours << endl;
    auto diff = tenHours - sixMin; // type: chrono::duration<double, ratio<60>>
    cout << diff << endl;

    // arithmetic operations of duration
    cout << boolalpha;
    cout << oneSec + sixMin << endl;    // d1 + d2
    cout << sixMin - oneSec << endl;    // d1 - d2
    cout << sixMin * 10 << endl;        // d * val
    cout << 10 * oneSec << endl;        // val * d
    cout << oneSec / 10 << endl;        // d / val, 0 second
    cout << sixMin / 10 << endl;                    // 0.6 minutes
    cout << sixMin / oneSec << endl;    // d1 / d2, get a factor: 360
    cout << oneSec % 10 << endl;        // d % val, calculate modulo. tick type should be integer types
    cout << tenHours % chrono::hours(6) << endl; // d1 / d2, modulo, result : 4 hours
    cout << (oneSec == chrono::milliseconds(1000)) << endl; // d1 == d2 : true
    // other comparison: != < <= > >=
    cout << endl;
    auto sec = chrono::seconds(1);
    cout << ++sec << endl; // increase one tick
    cout << sec++ << endl;
    cout << sec << endl;
    cout << --sec << endl; // 2 second
    chrono::seconds d(1);
    d += sec;
    cout << d << endl;
    // other compund assignment : -=d2 *=val /=val %=val %=d2

    cout << endl;
    cout << chrono::nanoseconds(oneSec) << endl; // copy construct, second to nanosecond, otherwise won't compile.
    // cout << chrono::seconds(chrono::milliseconds(7010)) << endl; // will not compile
    // but duration_cast can do it.
    cout << chrono::duration_cast<chrono::seconds>(chrono::milliseconds(7010)) << endl; // the 10 milliseconds will be lost.

    // but if the tick type is double, it will compile, (if only it exists implicitly conversion for them).
    cout << chrono::duration<double>(chrono::duration<double, std::milli>(10)) << endl;
    return 0;
}
