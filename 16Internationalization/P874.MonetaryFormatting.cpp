#include <iostream>
#include <locale>
#include <iomanip> // for put_money/get_money
using namespace std;

// monetary formatting:
// monetarypunct: define the format of monetary
// money_get: parsing monetary
// money_put: formatting monetary

// for money_base::pattern
ostream& operator<<(ostream& os, moneypunct<char>::pattern p)
{
    for (int i = 0; i < 4; ++i)
    {
        auto f = p.field[i];
        os << (f == money_base::none ? "none" :
               f == money_base::space ? "space" :
               f == money_base::symbol ? "symbol" :
               f == money_base::sign ? "sign" :
               f == money_base::value ? "value" :
              "???") << " ";
    }
    return os;
}

template<bool i18n>
void printMoneyPunct(const string& localeName)
{
    locale loc(localeName);
    const moneypunct<char, i18n>& mp = use_facet<moneypunct<char, i18n>>(loc);
    cout << "moneypunct in locale \"" << loc.name() <<"\": " << endl;
    cout << "decimal_point: " << mp.decimal_point() << endl;
    cout << "thousands_sep: " << mp.thousands_sep() << endl;
    cout << "grouping: ";
    for (auto c : mp.grouping())
    {
        cout << static_cast<int>(c) << " ";
    }
    cout << endl;
    cout << "curr_symbol: " << mp.curr_symbol() << endl;
    cout << "postive_sign: " << mp.positive_sign() << endl;
    cout << "negative_sign: " << mp.negative_sign() << endl;
    cout << "frac_digits: " << mp.frac_digits() << endl;
    cout << "pos_format: " << mp.pos_format() << endl;
    cout << "neg_format: " << mp.neg_format() << endl;
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // monetary punctuation
    printMoneyPunct<true>("C");

    // monetary formatting
    const money_put<char>& mp = use_facet<money_put<char>>(cout.getloc());
    mp.put(ostreambuf_iterator<char>(cout), true, cout, '_', 1234.5678); // 1235, because fra_digits is 0
    cout << endl;
    mp.put(ostreambuf_iterator<char>(cout), true, cout, '_', "1234.5678"); // 1234
    cout << endl;

    // monetary parsing
    const money_get<char>& mg = use_facet<money_get<char>>(cin.getloc());
    ios_base::iostate err = ios_base::goodbit;
    long double val = 0; // target could long double or string.
    mg.get(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), true, cin, err, val);
    cout << "parsed monetary value: " << val << endl;

    // monetary manipulators
    // put_money (val)/(val, i18n)
    // get_money (valRef)/(valRef, i18n)
    cout << showbase;
    cout << put_money(100.1242, true) << endl;
    cin >> get_money(val, true);
    cout << "parsed value: " << val << endl;
    return 0;
}
