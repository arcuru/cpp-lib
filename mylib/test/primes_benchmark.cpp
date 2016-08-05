#include "primes.hpp"
#include <iostream>
#include <chrono>
#include <cassert>

using namespace std;

int main(int argc, char** argv)
{
    uint64_t tmp = 1000000;
    if ( argc > 1 )
        tmp = atol(argv[1]);

    // Time the initial sieve
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    Primes p;
    p.sieve(tmp);

    auto end = high_resolution_clock::now();

    duration<long double> time_span = duration_cast<duration<long double>>(end - start);
    std::cout << "Sieve up to " << tmp << " in ";
    std::cout << time_span.count() << " seconds." << std::endl;;

    start = high_resolution_clock::now();

    auto list = p.getList();

    end = high_resolution_clock::now();

    time_span = duration_cast<duration<long double>>(end - start);
    std::cout << "Creating list of length " << list.size() << ": ";
    std::cout << time_span.count() << " seconds.";
    std::cout << std::endl;

    uint64_t isprimeLimit = 500000000;
    isprimeLimit = tmp;
    if (tmp < isprimeLimit)
        p.sieve(isprimeLimit);

    start = high_resolution_clock::now();

    size_t count = 0;
    for (size_t i = 0; i < isprimeLimit; ++i)
        if (p.isPrime(i))
            ++count;

    end = high_resolution_clock::now();

    time_span = duration_cast<duration<long double>>(end - start);
    std::cout << "Checking primes up to " << tmp << " : ";
    std::cout << time_span.count() << " seconds.";
    std::cout << std::endl;

    // Check to make sure is counted correctly
    assert(count == list.size());

    return 0;
}
