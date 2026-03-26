#include "expression.hpp"
#include "stack.hpp"
#include <stdexcept>
#include <cctype>

namespace
{
  int priority(const std::string& op)
  {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "^") return 0;
    return -1;
  }

  bool isNumber(const std::string& s)
  {
    if (s.empty()) return false;
    for (char c : s)
    {
      if (!std::isdigit(c)) return false;
    }
    return true;
  }

  long apply(long a, long b, const std::string& op)
  {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    if (op == "%") return a % b;
    if (op == "^") return a ^ b;

    throw std::logic_error("unknown operator");
  }
}
