#include <iostream>
#include <random>
#include <algorithm>
#include <functional>
#include <sstream>
using namespace std;

// random engine is a stateful source of randomness.
// In different platforms, same random engine with same state will generate same sequences of random values.
// The exception is default_random_engine, it's implementation dependent, the engine it uses may differ between different platforms.

// In computer, there is no real randomness, if you want generated random numbers unexcepted, give random engine a random seed (like current timepoint).

// the advantage of expected randomness: different execution will generate same random sequence, it's good for test.

// detail of random engines:
// the STL supply 16 random engines:

// the special implemention dependent one: default_random_engine
//       universal engines                          predefined parameterized random engines
// basic engines:
//      linear_congruential_engine                  minstd_rand, minstd_rand0
//      mersenne_twister_engine                     mt19937, mt19937_64
//      substrct_with_carry_engine                  ranlux24_base, ranlux48_base
// engine adapters:
//      discard_block_engine
//      independent_bits_engine                     ranlux24, ranlux48 (adapter of ranlux24_base, ranlux48_base)
//      shuffle_order_engine                        knuth_b (adapter of minstd_rand0)

// operations of random engine:
//      engine e
//      engine e(seed)
//      engine e(e2)
//      e.seed()        // restore the random engine to initial state
//      e.seed(seed)
//      e()             // generate random values
//      e.discard(n)    // discard n random values
//      e1 == e2        // judge whether e1 and e2 have same state.
//      e1 != e2
//      ostream << e    // write state of e to stream
//      istream >> e    // resotre state of e from stream

template<typename Container>
void printElements(const Container& c)
{
    cout << "elements: ";
    for (auto val : c)
    {
        cout << val << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    mt19937 engine;
    mt19937 engine2;
    vector<int> vec(10);
    vector<int> vec2(10);
    generate(vec.begin(), vec.end(), ref(engine)); // pass by reference
    generate(vec2.begin(), vec2.end(), ref(engine2));
    printElements(vec);
    printElements(vec2);

    generate(vec.begin(), vec.end(), engine);
    printElements(vec);
    generate(vec.begin(), vec.end(), engine); // passed by value
    printElements(vec);
    engine.discard(2);
    generate(vec.begin(), vec.end(), engine);
    printElements(vec);

    cout << endl;
    stringstream ss;
    ss << engine; // save statess
    generate(vec.begin(), vec.end(), ref(engine));
    printElements(vec);
    ss >> engine; // restore states
    generate(vec.begin(), vec.end(), ref(engine));
    printElements(vec);
    return 0;
}
