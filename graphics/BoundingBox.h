//
// Created by Petr on 19.11.2019.
//

#ifndef UTILITIES_BOUNDINGBOX_H
#define UTILITIES_BOUNDINGBOX_H

namespace geo {
    class BoundingBox {
        glm::vec3 p1, p2;

        bool operator==(const AABB &rhs) const;

        bool operator!=(const AABB &rhs) const;

        friend std::ostream &operator<<(std::ostream &stream, const AABB &aabb);
    };
}


#endif //UTILITIES_BOUNDINGBOX_H
