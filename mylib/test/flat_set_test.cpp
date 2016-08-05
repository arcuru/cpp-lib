#include "flat_set.h"
#define BOOST_TEST_MODULE flat_set_test
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE( constructors_test )
{
    flat_set<int> c1;
    BOOST_CHECK_EQUAL(c1.size(), 0);
    BOOST_CHECK(c1.empty());

    flat_set<int> c2(c1);
    BOOST_CHECK_EQUAL(c2.size(), 0);
    BOOST_CHECK(c2.empty());
}

BOOST_AUTO_TEST_CASE( operators_test )
{
    flat_set<int> a;
    a.insert(1);

    flat_set<int> b = a;
    BOOST_CHECK_EQUAL(a.size(), b.size());
    BOOST_CHECK_EQUAL(b.size(), 1);
}

BOOST_AUTO_TEST_CASE( insert_test )
{
    flat_set<int> a;
    for (int i=0; i < 100; ++i)
        a.insert(i);
    BOOST_CHECK_EQUAL(a.size(), 100);
    
    for (int i=0; i < 100; ++i)
        a.insert(i);
    BOOST_CHECK_EQUAL(a.size(), 100);

    BOOST_CHECK(a.count(5));
    BOOST_CHECK(a.count(500) == 0);
}

BOOST_AUTO_TEST_CASE( erase_test )
{
    flat_set<int> a;
    a.erase(1);

    for (int i=0; i < 10; i++)
        a.insert(i);
    BOOST_CHECK_EQUAL(a.size(), 10);
    a.erase(10); // Erase non-existent entry
    BOOST_CHECK_EQUAL(a.size(), 10);

    // Check 9 is there and then gone
    BOOST_CHECK(a.count(9));
    a.erase(9);
    BOOST_CHECK(a.count(9) == 0);
    BOOST_CHECK_EQUAL(a.size(), 9);

    for (int i=0; i < 9; i++)
        a.erase(i);

    BOOST_CHECK(a.empty());

    for (int i=0; i < 10; ++i)
        a.insert(i);

    BOOST_CHECK_EQUAL(a.size(), 10);
    a.clear();
    BOOST_CHECK(a.empty());
}

BOOST_AUTO_TEST_CASE( bounds_test )
{
    flat_set<int> a;

    for (int i=0; i < 10; ++i)
        a.insert(i);

    BOOST_CHECK_EQUAL(*a.lower_bound(5), 5);
    BOOST_CHECK(a.lower_bound(50) == a.end());

}

