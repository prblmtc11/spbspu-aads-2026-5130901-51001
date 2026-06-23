#include <iostream>
#include <string>
#include "familymanager.h"
#include "vector.h"

namespace {
  yarmolinskaya::Vector<std::string> splitLine(const std::string& line)
  {
    yarmolinskaya::Vector<std::string> tokens;
    size_t start = 0;
    size_t end = line.find(' ');
    while (end != std::string::npos) {
      if (end != start) {
        tokens.push_back(line.substr(start, end - start));
      }
      start = end + 1;
      end = line.find(' ', start);
    }
    if (start < line.size()) {
      tokens.push_back(line.substr(start));
    }
    return tokens;
  }
}

int main()
{
  yarmolinskaya::FamilyManager manager;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    yarmolinskaya::Vector<std::string> tokens = splitLine(line);
    if (tokens.empty()) {
      continue;
    }
    std::string command = tokens;
    if (command == "make-tree" && tokens.size() >= 2) {
      manager.makeTree(tokens);
    } else if (command == "add" && tokens.size() >= 4) {
      manager.addPerson(tokens, tokens, std::stoi(tokens));
    } else if (command == "child" && tokens.size() >= 5) {
      manager.establishChild(tokens, tokens, tokens, std::stoi(tokens));
    } else if (command == "children" && tokens.size() >= 3) {
      manager.printChildren(tokens, tokens);
    } else if (command == "grandchildren" && tokens.size() >= 3) {
      manager.printGrandchildren(tokens, tokens);
    } else if (command == "grandparents" && tokens.size() >= 3) {
      manager.printGrandparents(tokens, tokens);
    } else if (command == "siblings" && tokens.size() >= 3) {
      manager.printSiblings(tokens, tokens);
    } else if (command == "merge-trees-by-person" && tokens.size() >= 4) {
      manager.mergeTreesByPerson(tokens, tokens, tokens);
    } else if (command == "merge-trees" && tokens.size() >= 4) {
      manager.mergeTreesByLastName(tokens, tokens, tokens);
    }
  }
  return 0;
}
