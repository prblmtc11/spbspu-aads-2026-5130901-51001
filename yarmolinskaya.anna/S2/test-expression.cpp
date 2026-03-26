#define BOOST_TEST_MODULE S2
#include <boost/test/included/unit_test.hpp>
#include "expression.hpp"

using namespace yarmolinskaya;

BOOST_AUTO_TEST_CASE(simple_add)
{
  BOOST_TEST(evaluateExpression("1 + 2") == 3);
}

BOOST_AUTO_TEST_CASE(priority)
{
  BOOST_TEST(evaluateExpression("2 + 3 * 4") == 14);
}

BOOST_AUTO_TEST_CASE(brackets)
{
  BOOST_TEST(evaluateExpression("( 2 + 3 ) * 4") == 20);
}

BOOST_AUTO_TEST_CASE(xor_operation)
{
  BOOST_TEST(evaluateExpression("5 ^ 3") == (5 ^ 3));
}
