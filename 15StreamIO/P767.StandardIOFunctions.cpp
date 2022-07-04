#include <iostream>
using namespace std;

// functions that read/write unformatted data(different from operator >>/<< that read/write formatted data)
// read:
//      get : (), (c), (s, num), (s, num, t)
//      getline : (s, num), (s, num, t)
//      read : (s, num)
//      readsome : (s, num)
//      other functions: gcount(), ignore(...), peek(), unget(), putback(c), tellg(), seekg()
// write:
//      put(c)
//      write(str, count)
//      flush()
//      other: tellp(), seekp()

// sentry object:
// construction: preprocessing before real I/O operations
// destruction: postprocessing after real I/O operations

int main(int argc, char const *argv[])
{
    char c;
    while (cin.get(c))
    {
        cout.put(c);
    }
    return 0;
}