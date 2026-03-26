#define BOOST_TEST_MODULE S2
#include <boost/test/included/unit_test.hpp>
#include "common/list.hpp"

using namespace yarmolinskaya;

BOOST_AUTO_TEST_CASE(push_and_iterate)
{
  List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);

  auto it = l.begin();
  BOOST_TEST(*it == 1); ++it;
  BOOST_TEST(*it == 2); ++it;
  BOOST_TEST(*it == 3);
}

BOOST_AUTO_TEST_CASE(push_front)
{
  List<int> l;
  l.push_front(2);
  l.push_front(1);

  BOOST_TEST(l.front() == 1);
}

BOOST_AUTO_TEST_CASE(pop_front)
{
  List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.pop_front();

  BOOST_TEST(l.front() == 2);
}
