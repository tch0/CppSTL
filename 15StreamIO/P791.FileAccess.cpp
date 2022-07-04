#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// file stream class: 
// basic_ifstream<> : derived from basic_istream<>, ifstream, wifstream
// basic_ofstream<> : derived from basic_ostream<>, ofstream, wofstream
// basic_fstream<> : derived from basic_iostream<>, fstream, wfstream
// basic_filebuf<> : derived from basic_streambuf<>, filebuf, wfilebuf
// manage file automatically, open in construtor, close in destructor.

// from C++11: file stream has rvalue and move semantic, so you can move and swap a file stream object.

// file flags: in std::ios_base domain / usually use in form of std::ios::in/...
// in : open for read, default for ifstream
// out: open for write, default for ofstream
// app: open for write in append mode
// ate: seek to the end of file after open the file. (ate means at end)
// trunc: remove all previous contents of file (truncate)
// binary: binary mode (do not replace special characters, like EOF, CR LF, etc) 
//          used for binary file and copying file, if treat file as text file, do not use this flag.
// use operaotr | combine above flags, as the second argument when construct i/ofstream.

// corresponding C mode:
// in                   "r"
// out/out|trunc        "w"
// out|app/app          "a"
// in|out               "r+"
// in|out|trunc         "w+"
// in|app/in|out|app    "a+"
// binary               add "b"
// ate                  jump to end after open file.

// open/close file:
// open(name), open(name, flags)
// close()
// is_open()

// random access:
// basic_istream<>: tellg(), seekg(pos), seekg(offset, rpos)
// basic_ostream<>: tellp(), seekp(pos), seekp(offset, rpos)
// rpos could be: std::ios:: beg/cur/end.
// type of pos is: std::ios::pos_type
// type of offset is: std::ios::off_type

void writeCharsetToFile(const string& filename)
{
    ofstream fout(filename);
    if (!fout)
    {
        cerr << "open file " << filename << " failed!" << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 32; i < 128; ++i)
    {
        fout << char(i) << endl;
    }
}

void outputFile(const string& filename)
{
    ifstream fin(filename);
    if (!fin)
    {
        cerr << "open file " << filename << " failed!" << endl;
        exit(EXIT_FAILURE);
    }
    cout << fin.rdbuf(); // print all contents
}

int main(int argc, char const *argv[])
{
    writeCharsetToFile("charset.out");
    outputFile("charset.out");

    // rvalue of file stream
    ofstream("charset.out", ios::app) << "file stream rvalue test"; // append
    return 0;
}