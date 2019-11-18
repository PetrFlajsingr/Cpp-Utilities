//
// Created by Petr on 18.11.2019.
//

#ifndef UTILITIES_CONFIG_H
#define UTILITIES_CONFIG_H

#include <type_traits>
#include <string>
#include "ConfigLoader.h"
#include <optional>

template<typename Container>
struct ConfigContainerTraits {
    template<typename T, typename Key>
    static std::optional<T> find(Container &, const Key &value);

    template<typename T, typename Key>
    static bool contains(Container &, const Key &value);

    template<typename T, typename Key>
    static void set(Container &, const Key &key, T &&value);
};

template <typename Container>
struct ConfigLoader {
    Container load(std::string_view path);
};

template <typename Container>
struct ConfigSaver {
    void save(Container &config, std::string_view path);
};

template<typename DataContainer, bool ReadOnly,
        typename Key = std::string>
class Config {
    using container_traits = ConfigContainerTraits<DataContainer>;
public:
    explicit Config(std::string_view path) : path(std::string(path)) {
        reload();
    }

    template<typename T>
    std::optional<T> get(const Key &key) {
        return container_traits::template find<T>(data, key);
    }

    template<typename T>
    T getDefault(const Key &key, const T &defaultValue) {
        if (auto found = get<T>(key); found.has_value()) {
            return found.value();
        }
        return defaultValue;
    }

    template<typename T, typename = std::enable_if_t<!ReadOnly>>
    Config &set(const Key &key, const T &value) {
        container_traits::set(data, key, value);
        return *this;
    }

    template<typename = std::enable_if_t<!ReadOnly>>
    void save() {
        ConfigSaver<DataContainer> saver;
        saver.save(data, path);
    }

    void reload() {
        ConfigLoader<DataContainer> loader;
        data = loader.load(path);
    }

private:
    DataContainer data;
    std::string path;
};


#endif //UTILITIES_CONFIG_H
