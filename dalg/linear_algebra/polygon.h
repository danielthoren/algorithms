#ifndef DALG_POLYGON
#define DALG_POLYGON

#include <vector>

#include "vec2d.h"
#include "line_segment.h"

namespace dalg
{

    /**
     * Author: Daniel Thorén
     *
     * Class representing a 2d polygon 
     */
    template<typename T>
    class Polygon
    {
    public:

	Polygon() = default;

	/**
	 * Constructs polygon from points
	 */
	Polygon(std::vector<Vec2d<T>> const& points) :
	    points{points}
	    {}

	/**
	 * Adds a new point between the given point and the one in front
	 * of it. Defaults to the end of the segments array
	 */
	void add_point(Vec2d<T> const& pt, T position = 0);
    

	std::vector<Vec2d<T>>& get_points();

	/**
	 * Returns all the line segment that this polygon concists of
	 *
	 * Time Complexity: O(n) n = points
	 *
	 * return: vector containing all LineSegments along the border
	 *         of the polygon
	 */
	std::vector<LineSegment<T>> get_segments() const;

	/**
	 * Calculates the area of the polygon and returns it. Awnswer is
	 * always posetive.
	 *
	 * Template F: Type of the area calculated, should usually be of
	 *             float type
	 *
	 * Time complexity: O(n) n = points
	 *
	 * return : The area of the polygon
	 */
	template <typename F = double>
	F get_area() const;
	
	/**
	 * Calculates the point on this polygon and the given line segment
	 * that are the closest.
	 *
	 * other : The line segment to compare distance to
	 *
	 * return: The closest points on the polygon and segment in the
	 *         following format:
	 *         pair<point on polygon, point on segment>
	 *
	 */
	std::pair<Vec2d<T>, Vec2d<T>>
	min_distance(LineSegment<T> const& linseg) const;


	/**
	 * Calculates the closest points on the given polygons
	 *
	 * other : The other polygon
	 *
	 * return: The closest points on the two polygons
	 */
	std::pair<Vec2d<T>, Vec2d<T>>
	min_distance(Polygon<T> const& other) const;
    
    
    private:

	std::vector<Vec2d<T>> points{};
    };
}

#include "polygon.tcc"

#endif
