#pragma once

#include <cstdint>
#include <vector>

const int L1D_CACHE_SIZE = 32768;

class primes_bitpack;

class Primes
{
    public:
        // Member functions
        Primes();
        ~Primes();

        // Test 1 number for prime
        bool isPrime(uint64_t n) const;

        // Calculate pi(x), number of primes below x
        uint64_t pi(uint64_t x = 0);

        // Get a vector full of primes up to limit
        const std::vector<uint64_t>& getList(uint64_t limit = 0);

        // Manually calculate the primes up to limit
        void sieve(uint64_t limit);

    private:
        void segmentedEratosthenes(uint64_t limit,
            uint32_t segment_bytes = L1D_CACHE_SIZE);

        std::vector<uint64_t> pList;
        primes_bitpack* pSieve;
};

