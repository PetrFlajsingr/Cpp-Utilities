//
// Created by Petr on 18.11.2019.
//

#ifndef UTILITIES_GLM_H
#define UTILITIES_GLM_H

#include <glm/glm.hpp>

template <class T, template <int, class, glm::qualifier> class Template> struct is_vec_specialization : std::false_type {};

template <template <int, class, glm::qualifier> class Template, int L, class T, glm::qualifier Q>
struct is_vec_specialization<Template<L, T, Q>, Template> : std::true_type {};

template <typename T> constexpr bool is_vec_specialisation_v = is_vec_specialization<std::decay_t<T>, glm::vec>::value;

#endif // UTILITIES_GLM_H
