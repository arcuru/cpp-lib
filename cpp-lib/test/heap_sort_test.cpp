#include "heap_sort.h"
#define BOOST_TEST_MODULE heap_sort_test
#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_CASE(int_sort_test) {
  srand(4); // Consistent numbers for testing
  vector<int> v(1e3);
  for (auto &x : v)
    x = rand();
  auto cpy(v);

  BOOST_CHECK(v == cpy);

  sort(begin(v), end(v));
  heap_sort(cpy);

  BOOST_CHECK(v == cpy);
}

BOOST_AUTO_TEST_CASE(uint_sort_test) {
  srand(4); // Consistent numbers for testing
  vector<unsigned int> v(1e3);
  for (auto &x : v)
    x = rand();
  auto cpy(v);

  BOOST_CHECK(v == cpy);

  sort(begin(v), end(v));
  heap_sort(cpy);

  BOOST_CHECK(v == cpy);
}
