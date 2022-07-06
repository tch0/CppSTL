#include <iostream>
#include <random>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

// random-number generator: include a random engine and a distribution

// random engine: generate evenly distributed random values between a min and max value.
//          it's a function object, call operator() will get a new random value.
// distribution: convert random values into random numbers, the latter ones are distributed in a range that user gives arguments to decide.
//          it's also a function object, receive a random engine as input, generate random numbers.

// The initial state of every engine has a clear definition which is not random.
//      if you want an unexpected initial state, give a random number as seed to the random engine. (like current timepoint)
//      or use seed() function change the state of a random engine.

// notice: 
//      Do not only use random engine but not specify a random ditribution.
//      be careful of a temporary random engine, their initial states will be the same.

int main(int argc, char const *argv[])
{
    default_random_engine dre;
    // integers between 10 and 20 (both included)
    uniform_int_distribution<int> di(10, 20);
    for (int i = 0; i < 20; ++i)
    {
        cout << di(dre) << " ";
    }
    cout << endl;

    // floating-point numbers between 10.0 and 20.0 (20.0 exclusive, default range is [0.0, 1.0)
    uniform_real_distribution<double> dr(10, 20);
    for (int i = 0; i < 20; ++i)
    {
        cout << dr(dre) << " ";
    }
    cout << endl;

    vector<int> vec(20);
    iota(vec.begin(), vec.end(), 0);
    shuffle(vec.begin(), vec.end(), dre); // give a random engine
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
