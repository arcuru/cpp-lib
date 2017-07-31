#include "lru_cache.h"
#define BOOST_TEST_MODULE lru_cache_test
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(constructors_test) {
  lru_cache<int, int> a(10);
  BOOST_CHECK_EQUAL(a.size(), 0);
  BOOST_CHECK_EQUAL(a.capacity(), 10);
  BOOST_CHECK_EQUAL(a.empty(), true);
}

BOOST_AUTO_TEST_CASE(insert_test) {
  const int N = 10;
  lru_cache<int, int> a(N);

  // Insert 1 value
  a.insert(0, 5);
  BOOST_CHECK_EQUAL(a.size(), 1);

  // Fill it up
  for (int i = 1; i < N; ++i)
    a.insert(i, 5);
  BOOST_CHECK_EQUAL(a.size(), N);

  // Check the overflow
  a.insert(N, 5);
  BOOST_CHECK_EQUAL(a.size(), N);
}

BOOST_AUTO_TEST_CASE(contains_test) {
  const int N = 10;
  lru_cache<int, int> a(N);
  // Fill it up
  for (int i = 0; i < N; ++i)
    a.insert(i, 5);
  BOOST_CHECK_EQUAL(a.size(), N);

  for (int i = 0; i < N; ++i)
    BOOST_CHECK(a.contains(i));
}

BOOST_AUTO_TEST_CASE(pop_back_test) {
  const int N = 10;
  lru_cache<int, int> a(N);
  // Fill it up
  for (int i = 0; i < N; ++i)
    a.insert(i, 5);
  BOOST_CHECK_EQUAL(a.size(), N);
  a.insert(N, 5);
  BOOST_CHECK_EQUAL(a.size(), N);
  BOOST_CHECK_EQUAL(a.contains(0), false);
  for (int i = 1; i <= N; ++i)
    BOOST_CHECK_EQUAL(a.contains(i), true);
}

BOOST_AUTO_TEST_CASE(reorder_test) {
  const int N = 10;
  // Check reordering at every position
  for (int evict = 0; evict < N; ++evict) {
    lru_cache<int, int> a(N);
    // Fill it up
    for (int i = 0; i < N; ++i)
      a.insert(i, i + 1);

    auto x = a.get(evict);
    BOOST_CHECK_EQUAL(x, evict + 1);

    for (int i = 1; i < N; ++i) {
      // Insert N-1 elements to evict all but 1 original ones
      a.insert(i + N, 5);
    }
    for (int i = 0; i < N; ++i) {
      BOOST_CHECK_EQUAL(a.contains(i), i == evict);
    }
  }
}
