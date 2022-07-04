#include <iostream>
#include <chrono>
#include <cstdlib>
#include <iomanip> // for put_time/get_time
using namespace std;

// class inheritance:
// ios_base
// basic_ios<> [uses basic_streambuf<>]
// basic_istream<> basic_ostream<>
//        basic_iostream<>

int main(int argc, char const *argv[])
{
    // cancel the synchronization with stdio
    std::ios::sync_with_stdio(false);
    
    // time input/output manipulator
    // output date: put_time
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now); // time_t is timepoint (typically second from UNIX epoch)
    tm* nowTm = localtime(&t); // calendar time
    cout << put_time(nowTm, "date: %x\ntime: %X\n") << endl;
    // date: 07/02/22
    // time: 13:01:12

    // read date: get_time
    tm* date = nullptr;
    cout << "new date: ";
    cin >> get_time(date, "%X");
    if (!cin)
    {
        cout << "invalid date fromat" << endl;
    }
    return 0;
}
