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
	Circle(Vec2d<T> const& pos, T radius) :
	    Shape<T>(pos, ShapeType::circle), radius{radius}
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

	T get_radius() const
	    {
		return radius;
	    }

    private:
	T radius;
    };
}

#include "circle.tcc"

#endif
