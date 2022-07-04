#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
using namespace std;

// Loose coupling that uses std::basic_ios::tie :
// connect an stream(input or output, s1) to an output stream(s2), their buffer will be synchronized,
// that means the buffer of output stream(s2) will be flushed before every input or output action of the another stream(s1).

// tie() : get current tied stream ostream in pointer, null pointer means no ostream tied now.
// tie(ostream* stream): tie another ostream, return old tied ostream, nullptr/NULL means disconecting.


// Tight Coupling that uses stream buffer:
// function rdbuf(): multiple stream share one buffer.

// std::basic_ios<>::
// rdbuf() : get a pointer that point to stream buffer
// rdbuf(streambuf*): install a new stream buffer to current stream, return previous buffer.

// notice:  The destruction of basic_i/ostream(only) does not free its stream buffer, don't worry about double free problem.
//              and does not even flush the buffer, flush should be called explicitly.
//          The destruction of other streams(file stream, string stream) will destroy the stream buffer that it allocated,
//              but will not destroy the stream buffer that rdbuf(streambuf*) set.
//          The format flag is in basic_istream/ostream, and one stream's flags do not affect other streams that share the same stream buffer.


// stream redirecting: by set stream's buffer.
// it means the redirection of streams can be manipulated by programs without the help of OS.
// notice:
//      record the old buffer so that we can recover it when we need. (use RAII to manage resource is a rather good choice)

// using one stream read and write:
// example: use fstream to read and write same file.
//          or, we could use two streams(in and out) manage one buffer to read and write a same file.

int main(int argc, char const *argv[])
{
    // cin is implicitly tied to cout
    // disconnect their connection, may imporve the efficiency of IO.
    cin.tie(nullptr);
    cerr.tie(&cout); // connect cerr to cout, the cout buffer will be flush before every error output.

    // tight coupling that share stream buffer
    ostream hexout(cout.rdbuf());
    hexout.setf(ios::hex, ios::basefield);
    hexout.setf(ios::showbase); // or hexout << showbase;
    // switch between decimal and hexadecimal output, same stream buffer, different format flags.
    hexout << "hexout: " << 127 << " ";
    cout << "cout: " << 127 << " ";
    cout << endl;

    // stream redirecting
    // redirect cout to a file stream
    {
        // RAII to manager the stream buffer
        auto del = [](streambuf* p) {
            cout.rdbuf(p);
        };
        
        // the buffer will be freed after fout goes out of the domain, avoid to use a invalidated buffer.
        // in order to do that, use RAII to manage resource is a good choice.
        ofstream fout("test.out");
        fout.copyfmt(cout);
        unique_ptr<streambuf, decltype(del)> originBuf(cout.rdbuf(fout.rdbuf()), del);
        cout << "this is supposed to be in test.out!" << endl;
    }
    cout << "this is supposed to be in console!" << endl;
    return 0;
}
