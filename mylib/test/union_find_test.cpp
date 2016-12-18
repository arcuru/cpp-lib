#include "union_find.h"
#define BOOST_TEST_MODULE union_find_test
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(constructors_test) {
  const auto N = 100;
  union_find a(N);
  BOOST_CHECK_EQUAL(a.size(), N);

  for (size_t i = 1; i < N; ++i) {
    BOOST_CHECK_EQUAL(false, a.find(i, i - 1));
  }
}

BOOST_AUTO_TEST_CASE(unite_test) {
  const auto N = 100;
  union_find a(N);

  // Unite odds and evens together
  for (size_t i = 2; i < N; ++i) {
    a.unite(i, i - 2);
  }

  for (size_t i = 1; i < N; ++i) {
    BOOST_CHECK(!a.find(i, i - 1));
  }

  for (size_t i = 2; i < N; i += 2) {
    BOOST_CHECK(a.find(0, i));
    BOOST_CHECK(a.find(1, i - 1));
  }
}
