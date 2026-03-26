#define BOOST_TEST_MODULE S2
#include <boost/test/included/unit_test.hpp>
#include "queue.hpp"

using namespace yarmolinskaya;

BOOST_AUTO_TEST_CASE(queue_basic)
{
  Queue<int> q;
  q.push(1);
  q.push(2);

  BOOST_TEST(q.front() == 1);
  q.pop();
  BOOST_TEST(q.front() == 2);
}
