#include <iostream>
#include <iterator>
#include <unistd.h> // mingw64 only in windows
using namespace std;

// see The C++ Standard Library P832, 15.13.2 for details

// a stream buffer that uses file descriptor
class fdoutbuf : public std::streambuf
{
protected:
    int fd;
public:
    fdoutbuf(int _fd) : fd(_fd) {}
protected:
    // flush one character to I/O port
    virtual int_type overflow(int_type c) override
    {
        if (c != char_traits<char>::eof())
        {
            char z = c;
            if (write(fd, &z, 1) != 1) // call UNIX system call write for writing characters to I/O port
            {
                return char_traits<char>::eof();
            }
        }
        return c;
    }
    // write multiple characters to I/O port
    virtual std::streamsize xsputn(const char* s, std::streamsize num) override
    {
        return write(fd, s, num);
    }
};

// stream class that use the fdoutbuf
class fdostream : public std::ostream
{
protected:
    fdoutbuf buf;
public:
    fdostream(int fd) : std::ostream(nullptr), buf(fd) // set null at construct ostream
    {
        rdbuf(&buf); // set buffer after buf constructed.
    }
};


// ostream buffer with capability of character buffer 
// write to standard output (file descriptor 1)
class outbuf : public streambuf
{
protected:
    static const int bufferSize = 20; // size of data buffer
    char buffer[bufferSize]; // the data buffer
public:
    outbuf()
    {
        setp(buffer, buffer + (bufferSize - 1)); // set the begin and end position of data buffer.
    }   
    virtual ~outbuf()
    {
        sync(); // flush buffer, derived classes should override this function
    }
protected:
    // flush the characters in the buffer
    int flushBuffer()
    {
        int num = pptr() - pbase(); // pbase() is current position to write(not a valid character yet), pptr is the begin position of buffer.
        if (write(1, buffer, num) != num) // to stdout
        {
            return EOF;
        }
        pbump(-num); // reset put pointer accordingly (to begining)
        return num;
    }

    // buffer full
    virtual int_type overflow(int_type c) override
    {
        if (c != EOF)
        {
            *pptr() = c;
            pbump(1);
        }
        // flush the buffer
        if (flushBuffer() == EOF) // error
        {
            return EOF;
        }
        return c;
    }
    // synchronize data with file/desitnation, flush the data in buffer
    // for the stream buffer with no behaviour of buffering, no need to override sync.
    virtual int sync() override
    {
        if (flushBuffer() == EOF)
        {
            return -1; // error
        }
        return 0;
    }
};

int main(int argc, char const *argv[])
{
    // application example of fdoutbuf/fdostream
    fdostream out(1); // stdout
    out << "127 in hexadecimal: " << hex << 127 << endl;

    // user-defined buffred stream buffer
    outbuf buf;
    ostream os(&buf);
    os << "buffed standard output: " << hex << 127 << endl;
    return 0;
}
