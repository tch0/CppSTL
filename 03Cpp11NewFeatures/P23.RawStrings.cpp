#include <string>
#include <iostream>

using namespace std;

// C++11 raw string
// begin with "( / "delim(
// end with )" / )delim"

// encoding prefix: u8(UTF-8) u(char16_t) U(char32_t) L(wchar_t)

int main(int argc, char const *argv[])
{
    cout << R"(hello\\)" << endl;
    cout << R"yes("(hell
    o)")yes" << endl;
    wcout << L"hello" << endl;
    cout << u8"你好" << endl; // remember chcp 65001
    return 0;
}
