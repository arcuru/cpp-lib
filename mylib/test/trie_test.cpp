#include "trie.h"
#define BOOST_TEST_MODULE trie_test
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(empty_test) {
  trie a;
  BOOST_CHECK_EQUAL(false, a.find(""));
  BOOST_CHECK_EQUAL(false, a.find("a"));
  BOOST_CHECK_EQUAL(false, a.find("abc"));
}

BOOST_AUTO_TEST_CASE(insert_test) {
  trie a;

  // Empty string is not a special case
  a.insert("");
  BOOST_CHECK_EQUAL(true, a.find(""));
  BOOST_CHECK_EQUAL(false, a.find("a"));

  a.insert("a");
  BOOST_CHECK_EQUAL(true, a.find("a"));

  a.insert("abc");
  BOOST_CHECK_EQUAL(true, a.find("a"));
  BOOST_CHECK_EQUAL(false, a.find("ab"));
  BOOST_CHECK_EQUAL(true, a.find("abc"));
  BOOST_CHECK_EQUAL(false, a.find("abcd"));
}

BOOST_AUTO_TEST_CASE(erase_test) {
  trie a;

  a.insert("");
  a.insert("a");
  a.insert("abc");

  BOOST_CHECK_EQUAL(true, a.find("abc"));

  a.erase("abc");

  BOOST_CHECK_EQUAL(true, a.find("a"));
  BOOST_CHECK_EQUAL(false, a.find("ab"));
  BOOST_CHECK_EQUAL(false, a.find("abc"));

  a.erase("");

  BOOST_CHECK_EQUAL(false, a.find(""));
  BOOST_CHECK_EQUAL(true, a.find("a"));
  BOOST_CHECK_EQUAL(false, a.find("abc"));

  a.insert("abcd");

  BOOST_CHECK_EQUAL(false, a.find(""));
  BOOST_CHECK_EQUAL(true, a.find("a"));
  BOOST_CHECK_EQUAL(false, a.find("ab"));
  BOOST_CHECK_EQUAL(false, a.find("abc"));
  BOOST_CHECK_EQUAL(true, a.find("abcd"));

  a.insert("abc");

  BOOST_CHECK_EQUAL(true, a.find("abc"));
}
