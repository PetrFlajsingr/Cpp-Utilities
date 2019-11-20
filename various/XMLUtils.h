//
// Created by Petr Flajsingr on 20/11/2019.
//

#ifndef UTILITIES_XMLUTILS_H
#define UTILITIES_XMLUTILS_H
#include <string>
#include <tinyxml2/tinyxml2.h>

namespace Xml {
struct Base {
  virtual ~Base() = default;
};
struct Tag : public Base {
  Tag(std::string name);
  std::string name;
};
struct Attribute : public Base {
  Attribute(std::string name, std::string value);
  std::string name;
  std::string value;
};
struct Index : public Base {
  Index(int index);
  int index;
};
} // namespace Xml

class NamedSiblingIterator {
  tinyxml2::XMLElement *current;
  bool valid = true;

public:
  NamedSiblingIterator(tinyxml2::XMLElement *element);
  static NamedSiblingIterator Invalid();

  NamedSiblingIterator &operator++();

  NamedSiblingIterator operator++(int);

  tinyxml2::XMLElement *operator*();

  bool operator==(const NamedSiblingIterator &rhs) const;
  bool operator!=(const NamedSiblingIterator &rhs) const;

  operator bool();
};

class NamedSiblingIteratorInterface {
  tinyxml2::XMLElement *current;

public:
  NamedSiblingIteratorInterface(tinyxml2::XMLElement *element);
  NamedSiblingIterator begin();
  NamedSiblingIterator end();
};

NamedSiblingIteratorInterface childrenByName(tinyxml2::XMLElement *element,
                                             const std::string &name);

#endif // UTILITIES_XMLUTILS_H
