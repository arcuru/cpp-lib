#include "heap.h"
#define BOOST_TEST_MODULE heap_test
#include <boost/test/unit_test.hpp>
#include <deque>

using namespace std;

BOOST_AUTO_TEST_CASE(constructors_test) {
  heap<int> h;
  BOOST_CHECK_EQUAL(h.size(), 0);
  BOOST_CHECK(h.empty());
}

BOOST_AUTO_TEST_CASE(single_insert_test) {
  heap<int> h;
  h.push(1);
  BOOST_CHECK_EQUAL(h.size(), 1);
  BOOST_CHECK_EQUAL(h.top(), 1);
}

BOOST_AUTO_TEST_CASE(ordering_test) {
  heap<int> h;
  const int N = 10;
  for (int i = 1; i <= N; ++i) {
    h.push(i);
  }
  BOOST_CHECK_EQUAL(h.size(), N);
  BOOST_CHECK_EQUAL(h.top(), N);
}

BOOST_AUTO_TEST_CASE(deque_ordering_test) {
  heap<int, deque<int>> h;
  const int N = 10;
  for (int i = 1; i <= N; ++i) {
    h.push(i);
  }
  BOOST_CHECK_EQUAL(h.size(), N);
  BOOST_CHECK_EQUAL(h.top(), N);
}

BOOST_AUTO_TEST_CASE(reverse_ordering_test) {
  heap<int, vector<int>, std::greater<int>> h;
  const int N = 10;
  for (int i = 1; i <= N; ++i) {
    h.push(i);
  }
  BOOST_CHECK_EQUAL(h.size(), N);
  BOOST_CHECK_EQUAL(h.top(), 1);
}

BOOST_AUTO_TEST_CASE(pop_test) {
  heap<int> h;
  const int N = 10;
  for (int i = 1; i <= N; ++i) {
    h.push(i);
  }
  BOOST_CHECK_EQUAL(h.size(), N);
  for (int i = N; i > 0; --i) {
    BOOST_CHECK_EQUAL(h.top(), i);
    h.pop();
  }
  BOOST_CHECK(h.empty());
}

BOOST_AUTO_TEST_CASE(swap_test) {
  heap<int> a;
  heap<int> b;
  a.push(1);
  std::swap(a, b);
  BOOST_CHECK_EQUAL(b.size(), 1);
  BOOST_CHECK_EQUAL(b.top(), 1);
  BOOST_CHECK(a.empty());
}
