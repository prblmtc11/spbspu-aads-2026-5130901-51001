#ifndef YARMOLINSKAYA_PERSON_H
#define YARMOLINSKAYA_PERSON_H

#pragma once
#include <string>
#include "vector.h"

namespace yarmolinskaya {
  struct Person;

  struct Relation {
    Person* person = nullptr;
    int degree = 0;
  };

  struct Person {
  public:
    std::string m_name;
    int m_birthYear = 0;
    Vector<Relation> m_parents;
    Vector<Relation> m_children;

    Person() = default;
    Person(std::string n, int year)
    {
      m_name = std::move(n);
      m_birthYear = year;
    }

    std::string getLastName() const
    {
      size_t space = m_name.find(' ');
      if (space == std::string::npos) {
        return m_name;
      }
      return m_name.substr(0, space);
    }
  };
}

#endif
