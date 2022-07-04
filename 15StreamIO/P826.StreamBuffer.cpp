#include <iostream>
#include <iomanip>
#include <iterator> // for i/ostreambuf_iterator
#include <string>
#include <algorithm>
using namespace std;

// basic_streambuf<charT, traits> :     streambuf/wstreambuf
// basic_filebuf<charT, traits> :       filebuf/wfilebuf
// basic_stringbuf<charT, traits> :     stringbuf/wstringbuf

// stream buffer: for users, it's just a place that we can write characters into and read characters from.

// write interfaces:
// sputc(c) : put character c into buffer
// sputn(s, n) : put n charcters in charcter sequence s into buffer, return the number actually write into buffer

// read interfaces:
// in_avail() : return the lower bound (at least) remain character number.
// sgetc() : return current character without consuming it
// sbumpc() : return current charcter and cosuming it
// snextc() : return next charcter and cosuming current charcter
// sgetn(b, n) : comsuming n characters and save the to buffer b
// sputbackc(c) : put c back stream buffer (notice that only one charcter can be put back)
// sungetc() : put back last charcater (notice that only one charcter can be put back)

// other intefaces:
// install and return locale object : pubimbut(loc), getloc()
// seek to other position : pubseekpos (pos)/(pos, which)
//                          pubseekoff (offset, rpos)/(offset, rpos, which)
//      absolute or relative location
//      in or out (default both, argument which).
//      get current location: (type ios::pos_type), sbuf.pubseekoff(0, std::ios::cur)
// pubsetbuf(buf, n) : affect buffer behaviour

// iterator of stream buffer:
// it's input and output iterator : can write and read.
// in <iterator>
// input iterator: istreambuf_iterator<charT, traits>, read action will call sgetc()
// output iterator: ostreambuf_iterator<char, traits>, write action will call sputc(c)
// notice:
//          just like istream_iterator/ostream_iterator
//          can be passed to generic algorithms

int main(int argc, char const *argv[])
{
    // output stream buffer iterator
    std::ostreambuf_iterator<char> bufWriter(cout);// or construct it with cout.rdbuf()
    string s = "hello";
    copy(s.begin(), s.end(), bufWriter);
    cout << endl;

    // use stream buffer iterator implement a filter framework
    istreambuf_iterator<char> inpos(cin);
    istreambuf_iterator<char> endpos; // end of stream
    ostreambuf_iterator<char> outpos(cout);
    while (inpos != endpos)
    {
        *outpos = *inpos;
        ++inpos; // call submpc() to comsuming current charcter
        ++outpos; // no real operation
    }
    // or just pass stream buffer iterator into generic algorithms
    copy(inpos, endpos, outpos);
    return 0;
}
