//
// Created by Petr on 18.11.2019.
//

#ifndef UTILITIES_JSONCONFIG_H
#define UTILITIES_JSONCONFIG_H

#include "Config.h"
#include <nlohmann/json.hpp>
#include <fstream>

template <>
struct ConfigContainerTraits<nlohmann::json> {
    template <typename T, typename Key>
    static std::optional<T> find(nlohmann::json &container, const Key &key) {
        if (auto iter = container.find(key); iter != container.end()) {
            return static_cast<T>(*iter);
        }
        return std::nullopt;
    }
    template <typename T, typename Key>
    static bool contains(nlohmann::json &container, const Key &key) {
        return container.contains(key);
    }
    template <typename T, typename Key>
    static void set(nlohmann::json &container, const Key &key, T &&value) {
        container[key] = value;
    }
};


template <>
struct ConfigLoader<nlohmann::json> {
    nlohmann::json load(std::string_view path) {
        std::ifstream stream{std::string(path)};
        nlohmann::json result;
        stream >> result;
        return result;
    }
};

template <>
struct ConfigSaver<nlohmann::json> {
    void save(nlohmann::json &config, std::string_view path) {
        std::ofstream stream{std::string(path)};
        stream << config;
    }
};

template <bool ReadOnly>
using JsonConfig = Config<nlohmann::json, ReadOnly>;

#endif //UTILITIES_JSONCONFIG_H
