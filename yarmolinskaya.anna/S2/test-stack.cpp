#define BOOST_TEST_MODULE S2
#include <boost/test/included/unit_test.hpp>
#include "stack.hpp"

using namespace yarmolinskaya;

BOOST_AUTO_TEST_CASE(stack_basic)
{
  Stack<int> s;
  s.push(1);
  s.push(2);

  BOOST_TEST(s.top() == 2);
  s.pop();
  BOOST_TEST(s.top() == 1);
}

BOOST_AUTO_TEST_CASE(stack_empty_throw)
{
  Stack<int> s;
  BOOST_CHECK_THROW(s.top(), std::logic_error);
}
