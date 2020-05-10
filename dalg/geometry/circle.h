
#include "vec2d.h"

namespace dalg
{
    template <typename T>
    class Circle
    {
    public:
	Circle(Vec2d<T> const& pos, T radius) :
	    pos{pos}, radius{radius}
	    {}

	bool collision(Circle<T> const& other)
	    {
		T r = radius + other.radius;		
		r *= r;

		return r < ((pos.x + other.pos.x)^2) + ((pos.y + other.pos.y)^2);
	    }

	Vec2d<T> pos;
	T radius;
    };

}
