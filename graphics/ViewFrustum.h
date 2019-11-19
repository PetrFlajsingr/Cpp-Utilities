//
// Created by Petr on 19.11.2019.
//

#ifndef UTILITIES_VIEWFRUSTUM_H
#define UTILITIES_VIEWFRUSTUM_H

#include <array>
#include <glm/vec4.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include "BoundingBox.h"
#include "BoundingSphere.h"

namespace geo {
    enum class FrustumPosition {
        Inside, Outside, Intersection
    };

    class ViewFrustum {
        std::array<glm::vec4, 6> planes;

        static ViewFrustum FromProjectionView(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);

        [[nodiscard]] FrustumPosition contains(const BoundingBox<3> &aabb) const;

        [[nodiscard]] FrustumPosition contains(const BoundingSphere<3> &bs) const;
    };
}


#endif //UTILITIES_VIEWFRUSTUM_H
