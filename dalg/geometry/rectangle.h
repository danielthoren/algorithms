
#include <utility>
#include <vector>
#include <limits>

#include "vec2d.h"
#include "line_segment.h"

namespace dalg
{
    template <typename T>
    class Rectangle
    {
    public:
	Rectangle(Vec2d<T> const& c1, Vec2d<T> const& c2, Vec2d<T> const& c3, Vec2d<T> const& c4) :
	    corners{c1, c2, c3, c4}
	    {}

	Rectangle(LineSegment<T> const& l1, LineSegment<T> const& l2) :
	    corners{l1.get_start_point(), l1.get_end_point(), l2.get_start_point(), l2.get_end_point()}
	    {}

	Rectangle(Rectangle<T> const& other) :
	    corners{ other.corners }
	    {}

	/**
	 * Returns the min and max value of all possible projections
	 * onto the given vec. This is done by projecting each corner
	 * onto vec and comparing them.
	 *
	 * Time Complexity: O(1)
	 *
	 * Template type is used to change return type from the
	 * default. This is useful when the Vec2d uses integer
	 * coordinates
	 *
	 * vec   : The vector to project onto
	 * return: The min and max value of the projections
	 *         pair<min, max>
	 */
	template <typename FL>
	std::pair<Vec2d<FL>, Vec2d<FL>> get_min_max_projection(Vec2d<T> const& vec)
	    {
		double min { std::numeric_limits<double>::max() };		
		Vec2d<FL> min_vec{};
		    
		double max { std::numeric_limits<double>::min() };
		Vec2d<FL> max_vec{};
		
		for (int i{0}; i < 4; i++)
		{
		    Vec2d<FL> res = project<T,FL>(corners[i], vec);
		    double res_len{ res.length() };

		    if (res_len > max)
		    {
			max = res_len;
			max_vec = res;
		    }
		    if (res_len < min)
		    {
			min = res_len;
			min_vec = res;
		    }
		}

		return {min_vec, max_vec};
	    }

	bool collision(Rectangle<T> const& other) const
	    {
		
	    }

	std::vector<Vec2d<T>>& get_corners()
	    {
		return corners;
	    }

    private:

	std::vector<Vec2d<T>> corners;
    };

}
