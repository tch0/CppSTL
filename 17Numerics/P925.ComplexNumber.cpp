#include <iostream>
#include <complex>
using namespace std;

// complex arithmetic

// implicit conversion of complex<>:
//      safe conversion can be implicitly done, like complex<float> to complex<double>
//      but unsafe conversion need do explicitly, like complex<double> to complex<int>/complex<float>, and complex<int> to complex<double>
// but assignment will be always valid because it's member template.

// real and imaginary parts, magnitude, angle:
// real(c) / imag(c)
// c.real() / c.imag()
// c.real(1.7) / c.imag(1.7) // set new real and imaginary
// magnitude: abs(c)
// squared magnitude: abs(c)
// phase angle: arg(c), equivalent to atan2(c.imag(), c.real())

// operator == and != are defined as global functions.
// There is no comparsion operators for complex. 
//      You can define a predicate for their sorting (like compre their magnitude and angle, or real and imaginary),
//      but it's no mathematical meaning.

// support operators: 
//      + - * / +(positive) -(negative) += -= *= /=
//      << >>, output format: (real, imag), formats that input stream accepts: (real, imag)/(real)/real

// transcendental functions: 
//      pow exp sqrt log log10
//      sin cos tan asin acos atan
//      sinh cosh tanh asinh acosh atanh

// types : complex<>::value_type

template<typename T>
void printComplex(const complex<T>& c, const string& name)
{
    cout << name << ": " << endl;
    cout << "  magnitude: " << abs(c) << endl;
    cout << "  squared magnitude: " << norm(c) << endl;
    cout << "  phase angle: " << arg(c) << endl;
}

int main(int argc, char const *argv[])
{
    complex<double> c1(4.0, 3.0);
    complex<double> c2(polar(5.0, 0.75));
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;

    printComplex(c1, "c1");
    printComplex(c2, "c2");

    cout << "c1 conjugated: " << conj(c1) << endl;
    cout << "c2 conjugated: " << conj(c2) << endl;  

    cout << "4.4 + c1 * 1.8: " << 4.4 + c1 * 1.8 << endl;
    cout << "4.4 + c2 * 1.8: " << 4.4 + c2 * 1.8 << endl;

    cout << "c1 + c2: " << c1 + c2 << endl;
    cout << "c1 += sqrt(c2): " << (c1 += sqrt(c2)) << endl;

    cout << "pow(c1, c2): " << pow(c1, c2) << endl;

    c1.real(10);
    cout << c1 << endl;
    return 0;
}
