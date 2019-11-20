//
// Created by Petr on 18.11.2019.
//

#include "config/XmlConfig.h"
#include "io/print.h"
#include <iostream>

int main() {
  constexpr auto path = "/Users/petr/CLionProjects/Utilities/test.xml";
  XmlConfig<false> config{path};

  const auto val =
      config.get<uint>(Xml::Tag{"label"}, Xml::Attribute{"name", "btn2"});

  print(val);
}