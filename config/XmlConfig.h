//
// Created by Petr Flajsingr on 20/11/2019.
//

#ifndef UTILITIES_XMLCONFIG_H
#define UTILITIES_XMLCONFIG_H

#include "Config.h"
#include "tinyxml2/tinyxml2.h"
#include "various/XMLUtils.h"
#include <io/print.h>
#include <memory>
#include <vector>

namespace {
using XmlContainer = std::unique_ptr<tinyxml2::XMLDocument>;

using KeysContainer = std::vector<std::reference_wrapper<const Xml::Base>>;
} // namespace

template <typename T>
std::optional<T> findByName(tinyxml2::XMLElement *el, const KeysContainer &keys,
                            unsigned int currentIndex = 0);

template <typename T>
void setByName(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *el, const T &value, const KeysContainer &keys, unsigned int currentIndex = 0) {
  if (auto der = dynamic_cast<const Xml::Tag *>(&(keys[currentIndex].get()));
      der != nullptr) {
    bool exists = false;
    for (const auto &element : childrenByName(el, der->name)) {
      exists = true;
      if (currentIndex == keys.size() - 1) {
        to_xml(value, element);
        break;
      } else {
        setByName<T>(doc, element, value, keys, currentIndex + 1);
      }
    }
    if (!exists) {
      auto element =
          dynamic_cast<tinyxml2::XMLElement*>(el->LinkEndChild(doc->NewElement(der->name.c_str())));
      if (currentIndex == keys.size() - 1) {
        auto toSetElement =
            dynamic_cast<tinyxml2::XMLElement*>(element->LinkEndChild(doc->NewElement("")));
        to_xml(value, toSetElement);
        return;
      }
      setByName<T>(doc, element, value, keys, currentIndex + 1);
    }
  } else {
    if (auto der =
          dynamic_cast<const Xml::Attribute *>(&(keys[currentIndex].get()));
        der != nullptr) {
      auto attr = el->Attribute(der->name.c_str(), der->value.c_str());
      if (attr != nullptr) {
        to_xml(value, el);
      }
    }
  }
}


template <> struct ConfigContainerTraits<XmlContainer> {
  using KeysContainer = std::vector<std::reference_wrapper<const Xml::Base>>;

  template <typename T, typename... Keys>
  static std::optional<T> find(XmlContainer &container, const Keys &... keys);

  template <typename T, typename... Keys>
  static bool contains(XmlContainer &container, const T &value,
                       const Keys &... keys);

  template <typename T, typename... Keys>
  static void set(XmlContainer &container, T &&value, const Keys &... keys) {
    KeysContainer tmpKeys{keys...};
    auto element = container->RootElement();
    setByName<T>(container.get(), element, value, tmpKeys);
  }
};

template <> struct ConfigLoader<XmlContainer> {
  XmlContainer load(std::string_view path);
};

template <> struct ConfigSaver<XmlContainer> {
  void save(XmlContainer &config, std::string_view path);
};

template <bool ReadOnly> using XmlConfig = Config<XmlContainer, ReadOnly>;

#include "XmlConfig.tpp"

#endif // UTILITIES_XMLCONFIG_H
