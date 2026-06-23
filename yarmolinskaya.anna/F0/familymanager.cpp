#include "FamilyManager.h"

void yarmolinskaya::FamilyManager::makeTree(std::string treeName)
{
  m_families.insert(treeName, NavTree());
}

void yarmolinskaya::FamilyManager::addPerson(std::string treeName, std::string name, int birthYear)
{
  NavTree* tree = m_families.find(treeName);
  if (!tree) {
    return;
  }
  if (tree->search(name) != nullptr) {
    return;
  }
  tree->insert(new Person(name, birthYear));
}

void yarmolinskaya::FamilyManager::establishChild(std::string treeName, std::string parentName, std::string childName, int degree)
{
  NavTree* tree = m_families.find(treeName);
  if (!tree) {
    return;
  }
  Person* p = tree->search(parentName);
  Person* c = tree->search(childName);
  if (!p || !c) {
    return;
  }
  for (size_t i = 0; i < c->m_parents.size(); ++i) {
    if (c->m_parents[i].degree == degree) {
      return;
    }
  }
  p->m_children.push_back({c, degree});
  c->m_parents.push_back({p, degree});
}

void yarmolinskaya::FamilyManager::printChildren(std::string treeName, std::string parentName)
{
  NavTree* tree = m_families.find(treeName);
  if (!tree) {
    return;
  }
  Person* p = tree->search(parentName);
  if (!p || p->m_children.empty()) {
    std::cout << "<NONE>\n";
    return;
  }
  for (size_t i = 0; i < p->m_children.size(); ++i) {
    std::cout << p->m_children[i].person->m_name << " " << p->m_children[i].person->m_birthYear << " <DEGREE: " << p->m_children[i].degree << ">\n";
  }
}

void yarmolinskaya::FamilyManager::printGrandchildren(std::string treeName, std::string name)
{
  NavTree* tree = m_families.find(treeName);
  if (!tree) {
    return;
  }
  Person* p = tree->search(name);
  if (!p) {
    return;
  }
  bool found = false;
  for (size_t i = 0; i < p->m_children.size(); ++i) {
    Person* child = p->m_children[i].person;
    for (size_t j = 0; j < child->m_children.size(); ++j) {
      int finalDegree = maxVal(p->m_children[i].degree, child->m_children[j].degree);
      std::cout << child->m_children[j].person->m_name << " " << child->m_children[j].person->m_birthYear << " <DEGREE: " << finalDegree + 1 << ">\n";
      found = true;
    }
  }
  if (!found) {
    std::cout << "<NONE>\n";
  }
}

void yarmolinskaya::FamilyManager::printGrandparents(std::string treeName, std::string name)
{
  NavTree* tree = m_families.find(treeName);
  if (!tree) {
    return;
  }
  Person* p = tree->search(name);
  if (!p) {
    return;
  }
  bool found = false;
  for (size_t i = 0; i < p->m_parents.size(); ++i) {
    Person* parent = p->m_parents[i].person;
    for (size_t j = 0; j < parent->m_parents.size(); ++j) {
      int finalDegree = maxVal(p->m_parents[i].degree, parent->m_parents[j].degree);
      std::cout << parent->m_parents[j].person->m_name << " " << parent->m_parents[j].person->m_birthYear << " <DEGREE: " << finalDegree << ">\n";
      found = true;
    }
  }
  if (!found) {
    std::cout << "<NONE>\n";
  }
}

void yarmolinskaya::FamilyManager::printSiblings(std::string treeName, std::string name)
{
  NavTree* tree = m_families.find(treeName);
  if (!tree) {
    return;
  }
  Person* self = tree->search(name);
  if (!self) {
    return;
  }
  bool found = false;
  for (size_t i = 0; i < self->m_parents.size(); ++i) {
    Person* parent = self->m_parents[i].person;
    for (size_t j = 0; j < parent->m_children.size(); ++j) {
      if (parent->m_children[j].person != self) {
        int finalDegree = maxVal(self->m_parents[i].degree, parent->m_children[j].degree);
        std::cout << parent->m_children[j].person->m_name << " " << parent->m_children[j].person->m_birthYear << " <DEGREE: " << finalDegree << ">\n";
        found = true;
      }
    }
  }
  for (size_t i = 0; i < self->m_parents.size(); ++i) {
    Person* parent = self->m_parents[i].person;
    for (size_t j = 0; j < parent->m_parents.size(); ++j) {
      Person* grandparent = parent->m_parents[j].person;
      for (size_t k = 0; k < grandparent->m_children.size(); ++k) {
        Person* uncleAunt = grandparent->m_children[k].person;
        if (uncleAunt != parent) {
          for (size_t m = 0; m < uncleAunt->m_children.size(); ++m) {
            int finalDegree = maxVal({self->m_parents[i].degree, parent->m_parents[j].degree, uncleAunt->m_children[m].degree});
            std::cout << uncleAunt->m_children[m].person->m_name << " " << uncleAunt->m_children[m].person->m_birthYear << " <DEGREE: " << finalDegree + 1 << ">\n";
            found = true;
          }
        }
      }
    }
  }
  if (!found) {
    std::cout << "<NONE>\n";
  }
}

void yarmolinskaya::FamilyManager::mergeTreesByPerson(std::string newTree, std::string t1, std::string t2)
{
  makeTree(newTree);
  NavTree* tree1 = m_families.find(t1);
  NavTree* tree2 = m_families.find(t2);
  if (!tree1 || !tree2) {
    return;
  }
  Vector<Person*> allP1 = tree1->getAllPersons();
  Vector<Person*> allP2 = tree2->getAllPersons();
  for (size_t i = 0; i < allP1.size(); ++i) {
    addPerson(newTree, allP1[i]->m_name, allP1[i]->m_birthYear);
  }
  for (size_t i = 0; i < allP2.size(); ++i) {
    NavTree* targetTree = m_families.find(newTree);
    if (targetTree && targetTree->search(allP2[i]->m_name) == nullptr) {
      addPerson(newTree, allP2[i]->m_name, allP2[i]->m_birthYear);
    }
  }
  for (size_t i = 0; i < allP1.size(); ++i) {
    Person* oldP = allP1[i];
    for (size_t j = 0; j < oldP->m_children.size(); ++j) {
      establishChild(newTree, oldP->m_name, oldP->m_children[j].person->m_name, oldP->m_children[j].degree);
    }
  }
  for (size_t i = 0; i < allP2.size(); ++i) {
    Person* oldP = allP2[i];
    for (size_t j = 0; j < oldP->m_children.size(); ++j) {
      establishChild(newTree, oldP->m_name, oldP->m_children[j].person->m_name, oldP->m_children[j].degree);
    }
  }
  std::cout << "<TREES MERGED>\n";
}

void yarmolinskaya::FamilyManager::mergeTreesByLastName(std::string newTree, std::string t1, std::string t2)
{
  makeTree(newTree);
  NavTree* tree1 = m_families.find(t1);
  NavTree* tree2 = m_families.find(t2);
  if (!tree1 || !tree2) {
    return;
  }
  Vector<Person*> allP1 = tree1->getAllPersons();
  Vector<Person*> allP2 = tree2->getAllPersons();
  for (size_t i = 0; i < allP1.size(); ++i) {
    addPerson(newTree, allP1[i]->m_name, allP1[i]->m_birthYear);
  }
  for (size_t i = 0; i < allP2.size(); ++i) {
    addPerson(newTree, allP2[i]->m_name, allP2[i]->m_birthYear);
  }
  for (size_t i = 0; i < allP1.size(); ++i) {
    Person* oldP = allP1[i];
    for (size_t j = 0; j < oldP->m_children.size(); ++j) {
      establishChild(newTree, oldP->m_name, oldP->m_children[j].person->m_name, oldP->m_children[j].degree);
    }
  }
  for (size_t i = 0; i < allP2.size(); ++i) {
    Person* oldP = allP2[i];
    for (size_t j = 0; j < oldP->m_children.size(); ++j) {
      establishChild(newTree, oldP->m_name, oldP->m_children[j].person->m_name, oldP->m_children[j].degree);
    }
  }
  for (size_t i = 0; i < allP1.size(); ++i) {
    for (size_t j = 0; j < allP2.size(); ++j) {
      if (allP1[i]->getLastName() == allP2[j]->getLastName() && allP1[i]->m_name != allP2[j]->m_name) {
        establishChild(newTree, allP1[i]->m_name, allP2[j]->m_name, 1);
      }
    }
  }
  std::cout << "<TREES MERGED>\n";
}
