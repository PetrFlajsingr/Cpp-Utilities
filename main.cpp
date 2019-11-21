//
// Created by Petr on 18.11.2019.
//

#include "config/XmlConfig.h"
#include "io/print.h"
#include "observable/observable.hpp"
#include <iostream>
#include <utility>

using String = StringDecorator<std::string>;
class Button {
  OBSERVABLE_PROPERTIES(Button);

public:
  Button() = default;
  explicit Button(String id) : id(std::move(id)) {}
  observable_property<String> text;
  observable_property<glm::vec3> position;
  observable_property<glm::vec3> dimensions;
  observable_property<bool> visible;
  observable_property<bool> enabled;

  void setEnabled(bool en) { enabled = en; }

  String getId() const { return id; }

private:
  String id;

  friend void from_xml<Button>(Button &value, tinyxml2::XMLElement *elem);
};

template <>
void to_xml<Button>(const Button &value, tinyxml2::XMLElement *elem) {
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
}

int main() {
  constexpr auto path = "/Users/petr/CLionProjects/Utilities/test.xml";
  XmlConfig<false> config{path};

  auto btn =
      config.get<Button>(Xml::Tag{"button"}, Xml::Attribute{"id", "btn1"})
          .value();

  print(btn.getId());
  btn.setEnabled(true);
  config.set(btn, Xml::Tag{"button"}, Xml::Attribute{"id", "btn1"});
  config.save();

  std::cout.flush();
}