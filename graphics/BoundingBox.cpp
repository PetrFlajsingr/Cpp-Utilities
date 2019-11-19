//
// Created by Petr on 19.11.2019.
//

#include "BoundingBox.h"

std::ostream &geo::operator<<(std::ostream &stream, const geo::AABB &aabb) {
    stream << "P1: [" << aabb.p1.x << ", " << aabb.p1.y << ", " << aabb.p1.z
           << "], P2: [ "
           << "]" << aabb.p2.x << ", " << aabb.p2.y << ", " << aabb.p2.z << "]";
    return stream;
}

bool geo::AABB::operator==(const geo::AABB &rhs) const {
    return p1 == rhs.p1 && p2 == rhs.p2;
}

bool geo::AABB::operator!=(const geo::AABB &rhs) const {
    return !(rhs == *this);
}