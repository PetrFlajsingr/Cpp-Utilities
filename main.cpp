//
// Created by Petr on 18.11.2019.
//

#include "config/JsonConfig.h"
#include "config/XmlConfig.h"
#include "containers/Tree.h"
#include "observable/observable.hpp"
#include "parallel/ThreadPool.h"
#include "types/Zip.h"
#include "various/isin.h"
#include "various/overload.h"
#include <iostream>
#include <parallel/Safe.h>
#include <utility>
#include <variant>
#include <various/ByteLiterals.h>

using String = StringDecorator<std::string>;

class Button {
  OBSERVABLE_PROPERTIES(Button);

public:
  Button() = default;

  explicit Button(String id) : id(std::move(id)) {}

  Button(const Button &other) {
    text = other.text.get();
    position = other.position.get();
    dimensions = other.dimensions.get();
    visible = other.visible.get();
    enabled = other.enabled.get();
    id = other.getId();
  }

  Button &operator=(const Button &other) {
    text = other.text.get();
    position = other.position.get();
    dimensions = other.dimensions.get();
    visible = other.visible.get();
    enabled = other.enabled.get();
    id = other.getId();
    return *this;
  }

  Button(Button &&other) = default;

  Button &operator=(Button &&other) = default;

  observable_property<String> text;
  observable_property<glm::vec3> position;
  observable_property<glm::vec3> dimensions;
  observable_property<bool> visible;
  observable_property<bool> enabled;

  void setEnabled(bool en) { enabled = en; }

  String getId() const { return id; }

  Button &setText(const String &text) {
    this->text = text;
    return *this;
  }

  Button &setPosition(glm::vec3 position) {
    this->position = position;
    return *this;
  }

  Button &setDimensions(glm::vec3 dimensions) {
    this->dimensions = dimensions;
    return *this;
  }

  friend void from_xml<Button>(Button &value, tinyxml2::XMLElement *elem);

private:
  String id;
};

template <> void to_xml<Button>(const Button &value, tinyxml2::XMLElement *elem) {
  elem->SetValue("button");
  elem->SetText(value.text.get().c_str());
  elem->SetAttribute("x", value.position.get()[0]);
  elem->SetAttribute("y", value.position.get()[1]);
  elem->SetAttribute("z", value.position.get()[2]);

  elem->SetAttribute("width", value.dimensions.get()[0]);
  elem->SetAttribute("height", value.dimensions.get()[1]);
  elem->SetAttribute("depth", value.dimensions.get()[2]);

  elem->SetAttribute("visible", value.visible.get());
  elem->SetAttribute("enabled", value.enabled.get());

  elem->SetAttribute("id", value.getId().c_str());
}

template <> void from_xml<Button>(Button &value, tinyxml2::XMLElement *elem) {
  value.id = elem->Attribute("id");
  auto text = elem->GetText();
  value.setPosition({std::stod(elem->Attribute("x")), std::stod(elem->Attribute("y")), std::stod(elem->Attribute("z"))})
      .setDimensions(
          {std::stod(elem->Attribute("width")), std::stod(elem->Attribute("height")), std::stod(elem->Attribute("depth"))})
      .setText(String{text == nullptr ? "" : text});
}

template <typename U, typename... T> void vis(U &ovr, std::variant<T...> &var) { std::visit(ovr, var); }
int main() {
  using namespace ByteLiterals;
  auto a = 1_GiB;
  print("A: ", a);
  Safe<int> protectedValue;
  {
    auto safeIntAccess = protectedValue.writeAccess();
    print(*safeIntAccess);
    *safeIntAccess = 10;
    print(*safeIntAccess);
    int test = 10 + *safeIntAccess;
    print(test);
  }

  glm::vec3 vec{1};
  print(vec);
  std::variant<int, double, std::string> var;
  var = 10;

  auto ovr = overload{
      [](int val) { print("int: ", val); },
      [](double val) { print("double: ", val); },
      [](std::string val) { print("string: ", val); },
  };
  vis(ovr, var);
  var = 1.0;
  vis(ovr, var);
  var = "test";
  vis(ovr, var);

  /*
  observable::value<int> a{11};
  observable::value<int> b{1212};
  observable::value<int> c{555};
  observable::value<int> d{3};
  observable::value<int> e{3};
  int wat = 10;
  a.subscribe([](auto &val) { print("a: ", val); });
  b.subscribe([](auto &val) { print("b: ", val); });
  c.subscribe([](auto &val) { print("c: ", val); });
  d.subscribe([](auto &val) { print("d: ", val); });
  e.subscribe([](auto &val) { print("e: ", val); });

  auto w = bindTo(wat, a);

  auto binding = bindBidirectional(a, b);
  auto binding2 = bindBidirectional(c, d);
  {auto binding1 = bindBidirectional(b, c);
    auto binding3 = bindTo(e, a);

    e = 1000;
    a = 10;
    d = 500;
  }

  a = 11;
  b = 100;

  print("wat: ", wat);*/

  /*constexpr auto path = "/Users/petr/CLionProjects/Utilities/test.xml";
  XmlConfig<false> config{path};

  auto btn =
      config.get<Button>(Xml::Tag{"button"}, Xml::Attribute{"id", "btn1"})
          .value();

  print(btn.getId());
  btn.enabled.subscribe([](auto val) { print(val); });
  btn.setEnabled(true);
  config.set(btn, Xml::Tag{"button"}, Xml::Attribute{"id", btn.getId()});
  btn.setEnabled(true);

  Button btn2{btn};
  print(btn2.getId());
  if (!config.contains(Xml::Tag{"button"}, Xml::Attribute{"id", "btn2"}))
    config.set(btn2, Xml::Tag{"button"}, Xml::Attribute{"id", "btn2"});
  else {
    btn2 = config.get<Button>(Xml::Tag{"button"}, Xml::Attribute{"id", "btn2"})
               .value();
  }
  print(btn2.getId());
  config.save();

  std::cout.flush();*/

  return 0;
}