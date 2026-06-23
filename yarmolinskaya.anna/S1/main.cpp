#include "sequence.hpp"

#include <iostream>
#include <stdexcept>

namespace yarmolinskaya
{
  class OverflowException : public std::runtime_error
  {
  public:
    List< NamedSequence > valid_data;
  };
}

int main()
{
  using namespace yarmolinskaya;
  List< NamedSequence > data;

  try
  {
    readSequences(data);
  }
  catch (const OverflowException &e)
  {
    const List< NamedSequence > &err_data = e.valid_data;

    if (err_data.empty())
    {
      std::cout << 0 << "\n";
    }
    else
    {
      printNames(err_data);
      processSequences(err_data);
    }

    std::cerr << "overflow\n";
    return 1;
  }

  if (data.empty())
  {
    std::cout << 0 << "\n";
    return 0;
  }

  printNames(data);
  processSequences(data);
  return 0;
}
