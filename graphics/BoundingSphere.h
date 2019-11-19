//
// Created by Petr on 19.11.2019.
//

#ifndef UTILITIES_BOUNDINGSPHERE_H
#define UTILITIES_BOUNDINGSPHERE_H

namespace geo {
    class BoundingSphere {
        glm::vec3 center;
        float radius;

        [[nodiscard]] float distance(glm::vec3 point) const {
            return glm::distance(center, point);
        }
    };
}


#endif //UTILITIES_BOUNDINGSPHERE_H
