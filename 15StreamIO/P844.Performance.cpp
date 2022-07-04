#include <iostream>
#include <iomanip>
using namespace std;

// Generally speaking, the performance of stream classes is already pretty efficient.
// but there also some ways of getting a better preformance.

// 1. include headers only needed (something will be done at run-time if include <iostream>)
// 2. cancel synchronization with C's standard streams, synchronization with C standard stream causes some unnecessary overhead.
//          and this means cancel concurrency support of streams.
// 3. buffering
//          the underlying system call is expensive, buffering mechanism is here to imporve this problem.
//      so disable flag unitbuf
//      try not to use manipulators that will flush the output stream (endl/flush/unitbuf)
//      tie() will also flush buffer, so try not to use tie to bind stream to another stream
// 4. use stream buffer inside the stream object directly
//      the stream obejct will create a sentry obejct to do something (like formatting,lock) when it uses the insdie stream obejct.
//      so if you need unformatted IO, use the inside stream buffer directly.
//      use operator<< and >> on stream buffer of cin/cout/...

int main(int argc, char const *argv[])
{
    bool old = std::ios::sync_with_stdio(false); // defined in std::ios_base as a static function
    cout << boolalpha << old << endl; // true

    // copy standard input to output !!!
    cout << cin.rdbuf();
    cin >> noskipws >> cout.rdbuf();
    return 0;
}
