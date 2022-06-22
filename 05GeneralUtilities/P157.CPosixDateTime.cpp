#include <iostream>
#include <ctime>
#include <chrono>
#include <stdexcept>
using namespace std;

// Date/Time utilities from C library
// types:
// clock_t : numeric type(usually 64 bits integer), elapsed CPU time, returned by clock()
// time_t : numeric type, represent a timepoint [usually the count of second from UNIX Epoch]
// struct tm : calendar time
// clock() : get elapsed CPU time, unit: 1/CLOCKS_PER_SEC second 
// time() : get current timepoint(time_t)
// difftime() : difference of two time_t, is a double, unit is second
// localtime() : covert time_t to a struct tm, time zone related
// gmtime() : convert time_t to a struct tm, time zone non-related
// asctime() : convet a struct tm to a standard calendar time string
// strftime() : convert a struct tm to a user-defined calendar time string
// ctime() : convert time_t to a standard calendar time string, equal to asctime(localtime(t))
// mktime() : convert struct tm to a time_t and query which day of a week and which day of a year

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

std::chrono::system_clock::time_point makeTimePoint(int year, int mon, int day, int hour, int min, int sec = 0)
{
    struct std::tm t;
    t.tm_sec = sec;
    t.tm_min = min;
    t.tm_hour = hour;
    t.tm_mday = day;
    t.tm_mon = mon - 1;
    t.tm_year = year - 1900;
    t.tm_isdst = -1;
    std::time_t tt = std::mktime(&t);
    if (tt == -1)
    {
        throw runtime_error("invalid system time");
    }
    return std::chrono::system_clock::from_time_t(tt);
}

int main(int argc, char const *argv[])
{
    auto tp1 = makeTimePoint(2022, 6, 22, 23, 30, 45);
    cout << timePointAsString(tp1) << endl; // Wed Jun 22 23:30:45 2022
    return 0;
}
