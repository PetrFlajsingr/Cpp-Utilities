//
// Created by Petr on 18.11.2019.
//

#ifndef UTILITIES_STRING_H
#define UTILITIES_STRING_H

template <typename T>
struct is_string : std::false_type {};

template <>
struct is_string<std::string> : std::true_type {};
template <>
struct is_string<const char*> : std::true_type {};
template <int N>
struct is_string<const char[N]> : std::true_type {};

#endif //UTILITIES_STRING_H
