//
// Created by Petr on 19.11.2019.
//

#ifndef UTILITIES_VIEWFRUSTUM_H
#define UTILITIES_VIEWFRUSTUM_H

namespace geo {
    class ViewFrustum {
        std::array<glm::vec4, 6> planes;

        static ViewFrustum FromProjectionView(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);

        [[nodiscard]] FrustumPosition contains(const AABB &aabb) const;

        [[nodiscard]] FrustumPosition contains(const BoundingSphere &bs) const;
    };
}


#endif //UTILITIES_VIEWFRUSTUM_H
