#include <iostream>
#include <iomanip>
using namespace std;

// manipulators that do not accept arguments correspond to member functions.
// manipulators that accept arguments correspoond to format flags.

// format flags: std::ios:xxx (enums in ios_base)
//      multiple flags in one group, combine to a musk.
// groups: adjustfield, basefield, floatfield, ...
// corresponding manipulator: std::xxx (function in namespace std), in <iomanip>
// member functions: setf(flags), setf(flags, mask/group), unsetf(flags), flags(), flags(flags), copyfmt(stream)
// manipulators: setiosflags(flags), unsetiosflags(mask)

// boolean I/O format: std::ios::boolalpha
// manipulator: boolalpha/noboolalpha

// width, fill, adjust field:
//      width only used on next formatted output/input, fill and adjust-field will continue to next change. 
// member functions : width(), width(val), fill(), fill(c)
// mask: adjustfield
// alignment flags: left, right, internal
// manipulators: setw(val), setfill(c), left, right, internal

// +/- symbol, uppercase:
//      + for positive numeric numbers
//      uppercase letters for hexadecimal numbers(include 0x/0X and digits) and scientific float numbers(e/E).
// flags: showpos, uppercase (default both unset)
// manipulators: showpos, noshowpos, uppercase, nouppercase

// numeric base:
// mask: basefield
// flags: oct, dec, hex (default is dec, do not support binary, if need binary input, use class bitset)
// manipulators: oct, dec, hex
// show base or not:
//      0x/0X for hex, 0 for decimal, default dec.
// flags: showbase
// manipulators: showbase, noshowbase

// floatint-point representation:
// flags: fixed, scientific, fixed|scientific
//      defualt is none, will use the most suitable one between the two flags
// musk: floatfield
// 
// show point or not: enfore show point . and trailing 0
// flags: showpoint
// 
// precision: defualt is 6 decimal places
// member function: precision(), percision(val)
// 
// all manipulators: showpoint, noshowpoint, setprecision(n), fixed, scientific, hexfloat, defaultfloat (corresponds to none flags).

// general formatting:
// flags: skipws, unitbuf
//      skip heading white spaces while read numerics. default is set.
//      flush output buffer after every writing. (cout/clog default unset, cerr default set)
// manipulators: skipws, noskipws, unitbuf, nounitbuf

int main(int argc, char const *argv[])
{
    // set flags directly
    cout.setf(std::ios::showpos | std::ios::uppercase);
    // use manipulators
    cout << showpos << uppercase;
    
    // show base and change base
    cout << showbase << hex;
    cout << 127 << endl;
    cout << cout.precision() << endl;

    return 0;
}