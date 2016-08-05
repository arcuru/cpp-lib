#include "primes.hpp"
#include <cmath>
#include <stdexcept>
#include <array>
#include <algorithm>

using std::vector;

/**
 * Internal class for accessing the special bit-packed primes data-type.
 *
 * Data is stored with 2, 3, 5 wheel factorization. 1 byte corresponds to
 * 30 numbers. 0's mark primes.
 * 
 */
class primes_bitpack {
    private:
        vector<uint8_t> data_; //!< Storage of bitpacked array
        uint64_t limit_; //!< Max stored prime

    public:

        primes_bitpack() : limit_(0) {}
        ~primes_bitpack() {}

        const vector<uint8_t>& getData() const
        {
            return data_;
        }

        uint64_t getLimit() const
        {
            return limit_;
        }

        /**
         * Creates a vector containing all the primes in the bitpack
         *
         * @param   limit   Upper bound.
         * @return  Vector holding all primes below limit.
         */
        vector<uint64_t> getList(uint64_t limit) const
        {
            if ( limit > limit_ )
                throw std::out_of_range("Prime hasn't been sieved.");
            uint64_t primeEnd = (limit / 30) + 1;

            vector<uint64_t> ret = {2, 3, 5};

            for (size_t n = 0; n < primeEnd; n++)
                for (uint8_t s = 1; s; s += s)
                    if (!(data_[n] & s))
                        ret.push_back(n*30 + bitToNum(s));

            while (!ret.empty() && ret.back() > limit)
                ret.pop_back();

            return ret;
        }

        /**
         * Reserves space for all the primes up to input.
         *
         * @param   limit   Max value to store.
         */
        void resize(uint64_t limit)
        {
            this->limit_ = limit;
            data_.resize((limit / 30) + 1, 0);
            set(1);
        }

        /**
         * Converts a set bit (0x01, 0x02, 0x04, etc) to prime offset value
         *
         * @param   bit Bit to convert
         * @return  Prime offset
         */
        inline uint64_t bitToNum(uint8_t bit) const
        {
            switch (bit) {
                case 0x01: return  1;
                case 0x02: return  7;
                case 0x04: return 11;
                case 0x08: return 13;
                case 0x10: return 17;
                case 0x20: return 19;
                case 0x40: return 23;
                case 0x80: return 29;
            }
            return 0;
        }

        /**
         * Converts a prime offset to it's bit position. If it's not an offset
         * then we return 0.
         *
         * @param   num Prime offset to check
         * @return  Bit vector to offset
         */
        inline uint8_t numToBit(uint64_t num) const
        {
            static std::array<uint8_t,30> lookup = {
                0, 0x01, 0, 0, 0, 0, 0, 0x02, 0, 0, 0, 0x04, 0, 0x08, 0, 0, 0, 0x10,
                0, 0x20, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0x80};
            return lookup[num];
        }

        /**
         * Checks if the bit for the input number is not set. Throws
         * out_of_range if input isn't within the bounds.
         *
         * @param   n   Number to test
         * @return  True if bit is set.
         */
        bool check(uint64_t n) const
        {
            if ( n > limit_ )
                throw std::out_of_range("Prime hasn't been sieved.");
            uint8_t mask = numToBit(n % 30);
            if (!mask)
                return false;
            return !(data_[n / 30] & mask);
        }

        /**
         * Sets bit to to mark that the number is not prime. Fails silently
         * if not in bounds
         *
         * @param   n   Number to mark not prime
         */
        void set(uint64_t n)
        {
            if ( n > limit_ )
                return;
            data_[n / 30] |= numToBit(n % 30);
        }

};

Primes::Primes()
{
    pSieve = new primes_bitpack();
}

Primes::~Primes()
{
    delete pSieve;
}

/**
 * Checks if a number is primes in the most efficient available way.
 *
 * @param   n   Number to test
 * @return  True if n is prime
 */
bool Primes::isPrime(uint64_t n) const
{
    if (n < 10) {
        if (n < 2)
            return false;
        if (n < 4)
            return true;
        if (!(n & 1))
            return false;
        if (n < 9)
            return true;
        return false;
    }
    if (!(n & 1))
        return false;
    if (!(n % 3))
        return false;
    if (!(n % 5))
        return false;
    if (n < pSieve->getLimit())
        return pSieve->check(n);

    // Check possible primes after 2,3,5 wheel factorization
    uint64_t f = 7;
    while (f * f <= n) {
        if (!(n % f))
            return false;
        if (!(n % (f += 4)))
            return false;
        if (!(n % (f += 2)))
            return false;
        if (!(n % (f += 4)))
            return false;
        if (!(n % (f += 2)))
            return false;
        if (!(n % (f += 4)))
            return false;
        if (!(n % (f += 6)))
            return false;
        if (!(n % (f += 2)))
            return false;
        f += 6;
    }
    return true;
}

/**
 * Generate a compact array of all primes up to the limit. Speeds up
 * future functions, but requires (limit / 30) bytes.
 *
 *  @param  limit   End value of primes.
 */
void Primes::sieve(uint64_t limit)
{
    segmentedEratosthenes(limit);
}

/**
 * Get a list of all primes up to limit.
 *
 * @param   limit   End value of primes. Default is all sieved primes.
 * @return  Vector of primes
 */
const vector<uint64_t>& Primes::getList(uint64_t limit)
{
    // Special case for default
    if (0 == limit)
        limit = pSieve->getLimit();

    if (limit == 0)
        throw std::domain_error("Need limit.");

    if (limit > pSieve->getLimit())
        sieve(limit);

    pList = pSieve->getList(limit);
    return pList;
}

/**
 * Calculates pi(x), the number of primes less than or equal to x.
 *  It will manually count if the list is available, otherwise it will
 *  calculate the upper bound according to the formula:
 *      pi(x) <= (x/logx)(1 + 1.2762/logx)
 *
 * @param   x   Limit
 * @return  Number of primes less than or equal to input
 */
uint64_t Primes::pi(uint64_t x)
{
    // Counts the number of primes less than or equal to n
    if (0 == x)
        x = pSieve->getLimit();
    if (!pList.empty() && x <= pSieve->getLimit()) {
        vector<uint64_t>::iterator low;
        low = std::upper_bound(pList.begin(), pList.end(), x);
        return low - pList.begin();
    }
    if (x <= pSieve->getLimit()) {
        // Count elements in psieve
        // TODO: account for getting to the exact right number
        // Right now it counts up to the next multiple of 30
        uint64_t primeEnd = (x / 30) + 1;
        uint64_t top = 3;
        const vector<uint8_t> primes = pSieve->getData();
        for (uint64_t i = 0; i <= primeEnd; i++) //Counts primes
            for (uint8_t s = 1; s; s += s)
                if (!(primes[i] & s))
                    top++;
        return top;
    }
    // Estimate if it's higher than we have numbers for
    return (x/log(x))*(1 + (1.2762/log(x)));
}

/**
 * Perform the segmented Sieve of Eratosthenes. Store result in pSieve
 *
 * @param   limit           Upper bound.
 * @param   segment_bytes   Size of sieve segment (ideally size of L1 Data Cache)
 */
void Primes::segmentedEratosthenes(uint64_t limit, uint32_t segment_bytes)
{
    uint64_t s = 7; // For tracking which primes are needed per segment
    uint64_t segment_size = segment_bytes * 30;
    uint64_t sqrtLimit = std::sqrt(limit);
    uint64_t presieve = std::min(sqrtLimit, (uint64_t)std::sqrt(segment_size));

    // Create space in the bitpack
    pSieve->resize(limit);

    // Generate the min required to start sieving
    for (uint64_t i = 7; i * i <= presieve; i+=2)
        if (pSieve->check(i))
            for (uint64_t j = i * i; j <= presieve; j += i*2)
                pSieve->set(j);

    vector<std::pair<uint32_t, uint64_t>> primes;
    primes.reserve(pi(sqrtLimit));

    for (uint64_t low = 0; low <= limit; low += segment_size) {

        // current segment = interval [low, high]
        uint64_t high = std::min(low + segment_size - 1, limit);

        // store primes needed to cross off multiples
        for (; s * s <= high; s += 2)
            if (pSieve->check(s))
                primes.push_back(std::make_pair(s, s*s));

        // Sieve segment
        for (auto& p : primes) {
            const uint64_t num = p.first;
            uint64_t s = p.second;

            // Here we're only checking possible primes after wheel-factorization
            switch ((s/num)%30) do {
                case  1: pSieve->set(s); s+=num*6;
                case  7: pSieve->set(s); s+=num*4;
                case 11: pSieve->set(s); s+=num*2;
                case 13: pSieve->set(s); s+=num*4;
                case 17: pSieve->set(s); s+=num*2;
                case 19: pSieve->set(s); s+=num*4;
                case 23: pSieve->set(s); s+=num*6;
                case 29: pSieve->set(s); s+=num*2;
            } while(s<=high);
            p.second = s;
        }
    }
}

