
#ifndef DALG_COLLISION
#define DALG_COLLISION

#include <optional>

#include "shape.h"
#include "polygon.h"
#include "rectangle.h"

namespace dalg
{

    template <typename T>
    std::optional<Collision<T>>
    collision(Shape<T>* a, Shape<T>* b);

    /**
     * Checks collisions between the given circels and returns 
     */
    template <typename T>
    std::optional<Collision<T>>
    circle_circle_collision(Circle<T>& b, Circle<T>& a);
}

#include "collision.tcc"

#endif
