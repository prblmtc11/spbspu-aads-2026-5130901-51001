#include "sequence.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
  using namespace yarmolinskaya;
  List< NamedSequence > data;
  bool is_overflow = false;

  try
  {
    readSequences(data);
  }
  catch (const std::runtime_error &e)
  {
    is_overflow = true;
  }

  if (data.empty())
  {
    std::cout << 0 << "\n";
    if (is_overflow)
    {
      std::cerr << "overflow\n";
      return 1;
    }
    return 0;
  }

  printNames(data);
  processSequences(data);

  if (is_overflow)
  {
    std::cerr << "overflow\n";
    return 1;
  }

  return 0;
}
