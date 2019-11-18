//
// Created by Petr on 18.11.2019.
//

#ifndef UTILITIES_CONFIGLOADER_H
#define UTILITIES_CONFIGLOADER_H

#include <string>

template <typename Container>
struct ConfigLoader {
    Container load(std::string_view path);
};

template <typename Container>
struct ConfigSaver {
    void save(Container &config, std::string_view path);
};


#endif //UTILITIES_CONFIGLOADER_H
