#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <string>
using namespace std;

// 4 specific timepoint
// epoch time: defualt constructing of time_point
// current time: clock::now()
// minimum timepoint: time_point::min()
// maximum timepoint: time_point::max()

std::string timePointAsString(const std::chrono::system_clock::time_point& tp)
{
    // convert to system time
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts;
    if (char* p = std::ctime(&t))
    {
        ts = p;
        ts.resize(ts.size() - 1); // strip trailing newline
    }
    return ts;
}


// class template time_point: chrono::time_point<Clock, Duration>
// typically time_point only has a memeber of chrono::duration type
// operations of time_point:
// t()
// t(tp2)
// t(d)
// time_point_cast<C, D>(tp)  // cast to specific time_point of Clcok and Duration
// tp += d
// tp -= d
// tp + d
// d + tp
// tp - d
// tp1 - tp2 // get a duration
// comparison: == != < <= > >=
// tp.time_since_epoch() // get a duration
// time_point::min() // minimum possible time_point
// time_point::max() // maximum possible time_point

int main(int argc, char const *argv[])
{
    // epoch of this system_clock
    std::chrono::system_clock::time_point tp; // Thu Jan 01 08:00:00 1970
    cout << "epoch: " << timePointAsString(tp) << endl;

    // print current time
    tp = std::chrono::system_clock::now(); // Wed Jun 22 15:50:37 2022
    cout << "current time: " << timePointAsString(tp) << endl;

    // print minimum time of system clock
    tp = std::chrono::system_clock::time_point::min(); // why invalid?
    cout << "minimum time: " << timePointAsString(tp) << endl;

    // print maximum time of system clcok
    tp = std::chrono::system_clock::time_point::max(); // Sat Apr 12 07:47:16 2262
    cout << "maximum time: " << timePointAsString(tp) << endl;

    cout << endl;
    {
        // test of time_point
        using Days = chrono::duration<int, ratio<3600*24>>;
        using Years = chrono::duration<int, ratio<3600*24*365>>;

        // epoch
        chrono::time_point<chrono::system_clock> tp;
        cout << "epoch: " << timePointAsString(tp) << endl;

        // add one day, 23 hours, and 55 minutes
        tp += Days(1) + chrono::hours(23) + chrono::minutes(55);
        cout << "later: " << timePointAsString(tp) << endl;

        // process difference of epoch in minutes and days
        auto diff = tp - chrono::system_clock::time_point(); // - epoch time, get duration
        cout << "diff: " << chrono::duration_cast<chrono::minutes>(diff).count() << " minutes" << endl;
        Days days = chrono::duration_cast<Days>(diff);
        cout << "diff: " << days.count() << " days" << endl;

        // substract one year
        tp -= Years(1);
        cout << "- 1 year: " << timePointAsString(tp) << endl;

        // substract 50 years
        tp -= Years(50);
        cout << "- 50 years: " << timePointAsString(tp) << endl;

        // substract 50 years again
        tp -= Years(50);
        cout << "- 50 years: " << timePointAsString(tp) << endl;

    }
    return 0;
}


// final: chrono is duration/timepoint library, not a data/time library
//        deal with epoch time, min and max timepoint, and leap years, leap seconds carefully when you use it represent date and time.