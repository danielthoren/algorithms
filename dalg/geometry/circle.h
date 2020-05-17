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
	    Shape<T>(pos), radius{radius}
	    {}

	std::optional<Collision<T>>
	collision(Shape<T>& other) override
	    {
		return other.circle_collision(*this);
	    }

	std::optional<Collision<T>>
	circle_collision(Circle<T>& other) override
	    {
		return circle_circle_collision(*this, other);
	    }

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

    /**
     * Checks collisions between the given circels and returns 
     */
    template <typename T>
    std::optional<Collision<T>>
    circle_circle_collision(Circle<T>& b, Circle<T>& a);

}

#include "circle.tcc"

#endif
