
#include "vec2d.h"

namespace dalg
{
    /**
     * Author: Daniel Thorén
     *
     * Class representing a Axis Aligned Boundry Box. This is used to make
     * fast collision checks between objects. Get two objects AABB:s then
     * check if they even have the possibility of colliding before
     * performing more expensive operations
     */
    template <typename T>
    class AABB
    {
    public:
	AABB(Vec2d<T> const& min, Vec2d<T> const& max):
	    min{min}, max{max}
	    {}

	bool collision(AABB<T> const& other)
	    {
		return (max.x > other.min.x &&
			min.x < other.max.x &&
			max.y > other.min.y &&
			min.y < other.max.y);
	    }

    private:
	Vec2d<T> min;
	Vec2d<T> max;	
    };

}
