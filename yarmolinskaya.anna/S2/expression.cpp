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

namespace yarmolinskaya
{
  long evaluateExpression(const std::string& line)
  {
    Stack<long> values;
    Stack<std::string> ops;

    std::string token;

    for (size_t i = 0; i <= line.size(); ++i)
    {
      if (i == line.size() || line[i] == ' ')
      {
        if (token.empty())
        {
          continue;
        }

        if (isNumber(token))
        {
          values.push(std::stol(token));
        }
        else if (token == "(")
        {
          ops.push(token);
        }
        else if (token == ")")
        {
          while (!ops.empty() && ops.top() != "(")
          {
            long b = values.top(); values.pop();
            long a = values.top(); values.pop();
            values.push(apply(a, b, ops.top()));
            ops.pop();
          }
          ops.pop();
        }
        else
        {
          while (!ops.empty() &&
                 priority(ops.top()) >= priority(token))
          {
            long b = values.top(); values.pop();
            long a = values.top(); values.pop();
            values.push(apply(a, b, ops.top()));
            ops.pop();
          }
          ops.push(token);
        }

        token.clear();
      }
      else
      {
        token += line[i];
      }
    }

    while (!ops.empty())
    {
      long b = values.top(); values.pop();
      long a = values.top(); values.pop();
      values.push(apply(a, b, ops.top()));
      ops.pop();
    }

    return values.top();
  }
}
