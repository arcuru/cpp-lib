#include "adjacency_list.h"
#define BOOST_TEST_MODULE adjacency_list_test
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(constructors_test) {
  const auto N = 100;
  adjacency_list<unweighted> a(N);
  BOOST_CHECK_EQUAL(a.size(), N);

  for (size_t i = 0; i < N; ++i) {
    BOOST_CHECK_EQUAL(0, a.neighbors(i).size());
  }
}

BOOST_AUTO_TEST_CASE(add_edge_test) {
  const auto N = 100;
  adjacency_list<unweighted> a(N);

  for (size_t i = 0; i < N; ++i) {
    a.add_edge(i, (i + 2) % N);
  }

  for (size_t i = 0; i < N; ++i) {
    BOOST_CHECK_EQUAL(1, a.neighbors(i).size());
  }

  for (size_t i = 0; i < N; ++i) {
    a.add_edge((i + 2) % N, i);
  }

  for (size_t i = 0; i < N; ++i) {
    BOOST_CHECK_EQUAL(2, a.neighbors(i).size());
  }
}
