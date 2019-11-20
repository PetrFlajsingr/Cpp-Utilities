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
                            unsigned int currentIndex = 0) {
  if (auto der = dynamic_cast<const Xml::Tag *>(&(keys[currentIndex].get()));
      der != nullptr) {
    print(der->name);
    for (const auto &element : childrenByName(el, der->name)) {
      print("Tag: ", element->Name());
      if (auto res = findByName<T>(element, keys, currentIndex + 1);
          res.has_value()) {
        return res;
      }
    }
    return std::nullopt;
  } else {
    if (auto der =
            dynamic_cast<const Xml::Attribute *>(&(keys[currentIndex].get()));
        der != nullptr) {
      print(der->name);
      auto attr = el->Attribute(der->name.c_str());
      print(attr);
      print(der->name);
      if (auto attr = el->Attribute(der->name.c_str());
          attr != nullptr && attr == der->value) {
        print("wa");
        return T{};
      }
      return std::nullopt;
    }
  }
  return std::nullopt;
}

template <> struct ConfigContainerTraits<XmlContainer> {
  using KeysContainer = std::vector<std::reference_wrapper<const Xml::Base>>;

  template <typename T, typename... Keys>
  static std::optional<T> find(XmlContainer &container, const Keys &... keys) {
    KeysContainer tmpKeys{keys...};
    auto element = container->RootElement();
    return findByName<T>(element, tmpKeys);
  }

  template <typename T, typename... Keys>
  static bool contains(XmlContainer &container, const T &value,
                       const Keys &... keys) {
    return false;
  }

  template <typename T, typename... Keys>
  static void set(XmlContainer &container, T &&value, const Keys &... keys) {}
};

template <> struct ConfigLoader<XmlContainer> {
  XmlContainer load(std::string_view path) {
    auto result = std::make_unique<tinyxml2::XMLDocument>();
    result->LoadFile(std::string(path).c_str());
    return result;
  }
};

template <> struct ConfigSaver<XmlContainer> {
  void save(XmlContainer &config, std::string_view path) {
    config->SaveFile(std::string(path).c_str());
  }
};

template <bool ReadOnly> using XmlConfig = Config<XmlContainer, ReadOnly>;

#endif // UTILITIES_XMLCONFIG_H
