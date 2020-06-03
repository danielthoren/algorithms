#ifndef DALG_CIRCLE
#define DALG_CIRCLE

#include <optional>

#include "vec2d.h"
#include "shape.h"

namespace dalg
{
    template <typename T>
    class Circle : public Shape<T>
    {
    public:
	Circle() = default;
	
	Circle(Vec2d<T> const& center, T radius) :
	    Shape<T>(ShapeType::circle), center{center}, radius{radius}
	    {}

	bool operator==(Circle<T>& other) const
	    {
		std::cout << "in circle operator" << std::endl;
		return radius == other.radius && this->pos == other.pos;
	    }

	bool operator!=(Circle<T>& other) const
	    {
		return !(*this == other);
	    }

	Vec2d<T> center;
	T radius;
    };
}

#include "circle.tcc"

#endif
