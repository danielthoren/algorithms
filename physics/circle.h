
#include "shape.h"

#include "../dalg/geometry/vec2d.h"
#include "../dalg/geometry/circle.h"

namespace phys
{
    template <typename T>
    class Circle : public dalg::Circle<T>, public Shape<T>
    {
	Circle() = default;
	
	Circle(dalg::Vec2d<T> const& center, T radius) :
	    dalg::Circle<T>{center, radius}, Shape<T>{center, ShapeType::circle}
	    {}
    };
}
