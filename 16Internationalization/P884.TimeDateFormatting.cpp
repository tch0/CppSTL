#include <iostream>
#include <locale>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;

// time facet:
// time parsing: time_get
// time formatting: time_put
// they all manipulate struct tm (define in <ctime>) object

// see https://zh.cppreference.com/w/cpp/io/manip/put_time
//      for conversion specifiers of time.

// IO manipulators in <iomanip>:
// put_time(tm*, fmt)
// get_time(tm*, fmt)


int main(int argc, char const *argv[])
{
    // current date time
    auto now = chrono::system_clock::now(); // timepoint
    time_t t = chrono::system_clock::to_time_t(now); // timepoint
    tm* nowTm = localtime(&t); // calendar time

    // date time formatting
    locale loc;
    const time_put<char>& tp = use_facet<time_put<char>>(loc);

    tp.put(cout, cout, ' ', nowTm, 'x'); // 07/06/22
    cout << endl;

    string format = "%A %x %I%p\n"; // weekday date hour
    tp.put(cout, cout, ' ', nowTm, format.c_str(), format.c_str() + format.size());
    // Wednesday 07/06/22 01PM

    // date time parsing
    try
    {
        const time_get<char>& tg = use_facet<time_get<char>>(loc);
        time_get<char>::dateorder d = tg.date_order();
        cout << "dateorder: " << (d == time_base::no_order || d == time_base::mdy ? "mdy" :
                                  d == time_base::dmy ? "dmy" :
                                  d == time_base::ymd ? "ymd" :
                                  d == time_base::ydm ? "ydm" : "Unkown") << endl;
        cout << "input time in format <weekday> <hh>:<mm>: ";
        struct tm val;
        string format = "%A %H:%M";
        ios_base::iostate err = ios_base::goodbit;
        tg.get(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), cin, err, &val, format.c_str(), format.c_str() + format.size());
        if (err != ios_base::goodbit)
        {
            cerr << "invalid date format" << endl;
            return EXIT_FAILURE;
        }
        string outFmt = "%A %H:%M";
        cout << "parsed time: ";
        tp.put(cout, cout, ' ', &val, outFmt.c_str(), outFmt.c_str() + format.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    // manipulators
    return 0;
}
