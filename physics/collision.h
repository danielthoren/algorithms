
#include <optional>

#include "../dalg/geometry/vec2d.h"
#include "shape.h"
#include "circle.h"

namespace phys
{

    template <typename T>
    std::optional<Collision<T>>
    collision(Shape<T>* a, Shape<T>* b);

    /**
     * Checks collisions between the given circels and returns 
     */
    template <typename T>
    std::optional<Collision<T>>
    circle_circle_collision(Circle<T> const& a, Circle<T> const& b);
}    
