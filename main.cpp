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
  auto text = elem->GetText();
  value
      .setPosition({std::stod(elem->Attribute("x")),
                    std::stod(elem->Attribute("y")),
                    std::stod(elem->Attribute("z"))})
      .setDimensions({std::stod(elem->Attribute("width")),
                      std::stod(elem->Attribute("height")),
                      std::stod(elem->Attribute("depth"))})
      .setText(String{text == nullptr ? "" : text});
}

int main() {
  constexpr auto path = "/Users/petr/CLionProjects/Utilities/test.xml";
  XmlConfig<false> config{path};

  auto btn =
      config.get<Button>(Xml::Tag{"button"}, Xml::Attribute{"id", "btn1"})
          .value();

  print(btn.getId());
  btn.setEnabled(true);
  config.set(btn, Xml::Tag{"button"}, Xml::Attribute{"id", btn.getId()});

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

  std::cout.flush();
}