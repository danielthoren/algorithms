
#include "vec2d.h"
#include "utility.h"

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
	AABB(Vec2d<T> const& min, Vec2d<T> const& max) : min{min}, max{max}
	    {
		format();
	    }

	bool collision(AABB<T> const& other)
	    {
		return (max.x >= other.min.x &&
			min.x <= other.max.x &&
			max.y >= other.min.y &&
			min.y <= other.max.y);
	    }

	Vec2d<T> get_min()
	    {
		return min;
	    }

	Vec2d<T> get_max()
	    {
		return max;
	    }

    private:
	void format()
	    {
		if (max.x < min.x)
		{
		    T tmp = max.x;
		    max.x = min.x;
		    min.x = tmp;
		}
		if (max.y < min.y)
		{
		    T tmp = max.y;
		    max.y = min.y;
		    min.y = tmp;
		}
	    }
	
	Vec2d<T> min;
	Vec2d<T> max;	
    };

}
