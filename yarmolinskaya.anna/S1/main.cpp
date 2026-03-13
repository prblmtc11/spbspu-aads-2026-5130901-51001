#include "sequence.hpp"

#include <iostream>

int main()
{
  using namespace yarmolinskaya;
  List< NamedSequence > data;
  std::cout << "Reading sequence\n";
  readSequences(data);
  return 0;
}
