//
// Created by Petr on 19.11.2019.
//

#ifndef UTILITIES_BOUNDINGSPHERE_H
#define UTILITIES_BOUNDINGSPHERE_H

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

namespace geo {
template <unsigned int Dimensions> struct BoundingSphere {
  using Point = glm::vec3;
  Point center;
  float radius;

  [[nodiscard]] float distance(Point point) const;
};
} // namespace geo

#include "BoundingSphere.tpp"
#endif // UTILITIES_BOUNDINGSPHERE_H
