//
// Created by Petr on 19.11.2019.
//

#ifndef UTILITIES_BOUNDINGBOX_H
#define UTILITIES_BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <ostream>

namespace geo {
    struct BoundingBox {
        glm::vec3 p1, p2;

        bool operator==(const BoundingBox &rhs) const;

        bool operator!=(const BoundingBox &rhs) const;

        friend std::ostream &operator<<(std::ostream &stream, const BoundingBox &aabb);
    };
}


#endif //UTILITIES_BOUNDINGBOX_H
