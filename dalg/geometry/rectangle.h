
#include <utility>
#include <vector>
#include <limits>
#include <sstream>

#include "vec2d.h"
#include "utility.h"

namespace dalg
{
    
    /**
     * Author: Daniel Thorén
     *
     * Class representing rectangle.
     */
    template <typename T>
    class Rectangle
    {
    public:

	/**
	 * The input points are expected to be in either clockwise or
	 * counter clockwise order, thus the pairs (c1, c3) (c2,c4)
	 * must be furthest from each other (opposing). The vectors
	 * between the points must have an angle of 90 degrees
	 */
	Rectangle(Vec2d<T> const& c1, Vec2d<T> const& c2, Vec2d<T> const& c3, Vec2d<T> const& c4) :
	    corners{c1, c2, c3, c4}
	    {
		if (90 - angle( c1 - c2, c2 - c3) > 0.01 ||
		    90 - angle( c2 - c3, c3 - c4) > 0.01 ||
		    90 - angle(c3 - c4, c4 - c1) > 0.01 ||
		    90 - angle(c4 - c1, c1 - c2) > 0.01)
		{
		    throw BadArgumentException("Rectangle point constructor: points not 90 degrees");
		}

		if ( (c1 - c3).length() < (c1 - c2).length())
		{
		    throw BadArgumentException("Rectangle point constructor: points not given in correct order");
		}
	    }

	/**
	 * Constructs a rectangle by using the "top_left" variable as
	 * the top left corner then expanding along the x and y axis
	 * with width and height
	 */
	Rectangle(Vec2d<T> const& top_left, T width_x, T height_y)
	    {
		corners[0] = top_left;
		corners[1] = top_left + Vec2d<T>(width_x, 0);
		corners[2] = top_left + Vec2d<T>(width_x, height_y);
		corners[3] = top_left + Vec2d<T>(width_x, 0);
	    }

	Rectangle(Rectangle<T> const& other) :
	    corners{ other.corners }
	    {}

	/**
	 * Returns the min and max projection of the foud points of
	 * the box onto the given vec. This is done by projecting each
	 * corner onto vec and comparing them.
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
	template<typename FL = double>
	std::pair<Vec2d<FL>, Vec2d<FL>> get_min_max_projection(Vec2d<T> const& vec) const
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

	/**
	 * Returns the point at the center of the box
	 *
	 * return: Vector containing the center point
	 */
	Vec2d<T> get_center_point() const
	    {
		return Vec2d<T>( (corners[0].x + corners[2].x) / 2, (corners[0].y + corners[2].y) / 2 );
	    }

	/**
	 * Checks if the rectangles are colliding. This is done by
	 * calculating the projections of all points of both
	 * rectangles onto the vector between the centers of the
	 * rectangle then comparing them to each other. This shows if
	 * there is any space between the rectangles.
	 *
	 * Time complexity: O(1)
	 * 
	 * other : The other rectangle to check collision with
	 *
	 * return: true if they collide, otherwise false
	 */
	bool collision(Rectangle<T> const& other) const
	    {
		Vec2d<T> center_diff = get_center_point() - other.get_center_point();
		
		std::pair<Vec2d<T>, Vec2d<T>> min_max_1 =
		    get_min_max_projection(center_diff);

		std::pair<Vec2d<T>, Vec2d<T>> min_max_2 =
		    other.get_min_max_projection(center_diff);


		T min_1 = min_max_1.first.length();
		T max_1 = min_max_1.second.length();

		T min_2 = min_max_2.first.length();
		T max_2 = min_max_2.second.length();

		if (max_1 < min_2 || max_2 < min_1)
		{
		    return false;
		}
		else
		{
		    return true;
		}
	    }

	std::vector<Vec2d<T>>& get_corners()
	    {
		return corners;
	    }

    private:

	std::vector<Vec2d<T>> corners;
    };

}
