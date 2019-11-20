//
// Created by Petr on 19.11.2019.
//

#ifndef UTILITIES_BOUNDINGBOX_H
#define UTILITIES_BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <ostream>

namespace geo {
    template<unsigned int Dimensions>
    struct BoundingBox {
        using Point = glm::vec3;
        Point p1, p2;

        bool operator==(const BoundingBox &rhs) const;

        bool operator!=(const BoundingBox &rhs) const;

        template<unsigned int Dims>
        friend std::ostream &operator<<(std::ostream &stream, const BoundingBox<Dims> &aabb);
    };
}

#include "BoundingBox.tpp"
#endif //UTILITIES_BOUNDINGBOX_H
