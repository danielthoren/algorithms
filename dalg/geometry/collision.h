
#ifndef DALG_COLLISION
#define DALG_COLLISION

#include <optional>

#include "shape.h"
#include "polygon.h"
#include "rectangle.h"

namespace dalg
{
    template <typename T>
    inline std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>>, Circle<T> >
    intersect(Circle<T> const& c0, Circle<T> const& c1);
}

#include "collision.tcc"

#endif
