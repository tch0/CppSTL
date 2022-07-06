#include <iostream>
#include <locale>
using namespace std;

// multibyte and wide-character:
// multibyte: the bytes of a character may change
// wide-character: constant bytes in one character (typically 2 and 4)

// charsets:
// ASCII: as we all know, 7bit
// ISO-Latin-1/ISO-8859-1: 8bit
// ISO-Latin-8/ISO-8859-15: 8bit
// UCS-2: 16bit fixed length
// UTF-8: multibyte, 1byte ~ 4bytes
// UTF-16: multibyte, 2bytes/4bytes
// UCS-4/UTF-32: 32bit fixed length

// BOM: Byte order mark, code point 0xFEFF encode with target encoding

// process charsets in C++:
// char: all 8bit charsets, and sometimes UTF-8
// char16_t: save UCS-2/UTF-16 characters
// char32_t: save UCS-4/UTF-32 characters
// wchar_t: usually equivalent to char16_t or char32_t

// char_traits<>: define all fundamental properties of character type.


int main(int argc, char const *argv[])
{
    wcout << "yes" << wcout.widen('\n') << "no" << endl;
    return 0;
}
