
#ifndef DALG_COLLISION
#define DALG_COLLISION

#include <optional>

#include "shape.h"
#include "polygon.h"
#include "rectangle.h"

namespace dalg
{
    /**
     * Handles intersection between two circles. Returns a point if
     * only the boundry of the circles are intersecting, otherwise a
     * pair of points. If there is no intersection then return
     * monostate. In the unlikely event that both circles intersects
     * in all possible points then returns that circle.
     *
     * c0 : The first circle
     * c1 : The second circle
     *
     * return : monostate         : no intersection
     *          Vec2d             : Only boundry intersection
     *          pair<Vec2d, Vec2d>: Two intersection points
     *          Circle            : Intersects everywhere along the circle
     */
    template <typename T>
    inline std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>>, Circle<T> >
    intersect(Circle<T> const& c0, Circle<T> const& c1);
}

#include "collision.tcc"

#endif
