//
// Created by Petr on 18.11.2019.
//

#include "config/XmlConfig.h"
#include "io/print.h"
#include <iostream>

int main() {
  constexpr auto path = "/home/petr/CLionProjects/Utilities/test.xml";
  XmlConfig<false> config{path};

  config.set<std::string>(std::string("test"), Xml::Tag{"str"}, Xml::Tag{"Testerino"});

   auto val = config.get<std::string>(Xml::Tag{"str"}, Xml::Tag{"Testerino"}, Xml::Tag{"string"});

   config.save();

  print(val);
  std::cout.flush();
}