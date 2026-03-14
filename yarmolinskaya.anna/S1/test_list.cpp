#define BOOST_TEST_MODULE Listtests
#include <boost/test/included/unit_test.hpp>

#include "list.hpp"

BOOST_AUTO_TEST_CASE(emptyList)
{
  yarmolinskaya::List< int > list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(pushBackTest)
{
  yarmolinskaya::List< int > list;

  list.push_back(1);
  list.push_back(2);

  auto it = list.begin();

  BOOST_TEST(*it == 1);
  ++it;
  BOOST_TEST(*it == 2);
}
