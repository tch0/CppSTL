#include <iostream>
#include <iomanip>
#include <memory>
#include <cassert>
#include <cstdlib>
using namespace std;

// state: std::ios_base::iostate (usually use std::ios::iostate)
// in std::ios_base domain: maintained by std::basic_ios<>
//      goodbit: all good
//      eofbit: EOF
//      failbit: non-destructive(recoverable) failure, usually read format error, EOF.
//      badbit: destructive(irrecoverable) failure

// call basic_ios<>::exceptions(flag): set(or get with no argument) the flags that will arises td::ios_base::failure exception

// the advantage of using exceptions for stream state:
//      user defined error message
//      user defined error class
// disadvantage: complicated

double readAndProcessSum(istream& is)
{
    using std::ios;
    double value, sum;
    ios::iostate oldExceptions = is.exceptions();
    // arise exceptions for failbit and badbit
    is.exceptions(ios::failbit | ios::badbit);

    try
    {
        sum = 0;
        while (cin >> value)
        {
            sum += value;
        }
    }
    catch(...)
    {
        // eof will not arise exception
        if (!is.eof())
        {
            is.exceptions(oldExceptions);
            throw;
        }
    }
    is.exceptions(oldExceptions);
    return sum;
}

int main(int argc, char const *argv[])
{
    double sum {};
    try
    {
        sum = readAndProcessSum(cin);
    }
    catch(const ios::failure& error)
    {
        cerr << "I/O exception: " << error.what() << endl;
        return EXIT_FAILURE;
    }
    catch(const std::exception& e)
    {
        cerr << "standard exception: " << e.what() << endl;
        return EXIT_FAILURE;
    }
    catch(...)
    {
        cerr << "unknown exception" << endl;
        return EXIT_FAILURE;
    }
    cout << "sum: " << sum << endl;
    return 0;
}