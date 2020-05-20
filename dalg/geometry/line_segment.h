#ifndef LINE_SEG
#define LINE_SEG

#include <variant>

#include "vec2d.h"

namespace dalg
{

    /**
     * Author: Daniel Thorén
     *
     * Class performing various line segment operations.
     * Line segment represented by its endpoints
     */
    template<typename T>
    class LineSegment
    {
    public:
	LineSegment(LineSegment<T> const& other)
	    :  p0{other.p0}, u{other.u}
	    {}
	
	LineSegment(Vec2d<T> const& p0, Vec2d<T> const& p1)
	    : p0{p0}, u{p1 - p0}
	    {}
    
	LineSegment(T x0, T y0, T x1, T y1)
	    : LineSegment<T>({x0, y0}, {x1, y1})
	    {}

	/**
	 * Checks if the two line segments are exactly the same
	 * (the same start and end points)
	 */
	bool operator==(LineSegment<T> const& other) const;
	bool operator!=(LineSegment<T> const& other) const;

	void operator=(LineSegment<T> const& other);

	/**
	 * Calculates the point on the line that is closest to the given pt
	 *
	 * pt    : The point to measure distance to
	 * return: The closest point on this line
	 */
	Vec2d<T> closest_point(Vec2d<T> const& pt) const;

	/**
	 * Calculates the points on the line segments that are the closest
	 * and returns them both
	 *
	 * lseg  : The other line segment
	 * return: The closest points on the line segments
	 *         std::pair<on this, on lseg>
	 */
	std::pair<Vec2d<T>, Vec2d<T>> closest_points(LineSegment<T> const& lseg) const;

	/**
	 * Returns true if this line contains the given point,
	 * otherwise false
	 */
	bool on_line(Vec2d<T> const& pt) const;

	/**
	 * Returns true if this linesegment contains the given point,
	 * otherwise false
	 */
	bool on_segment(Vec2d<T> const& pt) const;
	
	/**
	 * Returns the point where this Line and other intersects If they
	 * don't intersect then return point(std::numeric_limits<T>::min())
	 *
	 * other : The line to check for intersection with
	 * return: The intersection point. If there is non then return point with
	 *         std::numeric_limits<T>::min() as its values
	 */
	std::variant<std::monostate, Vec2d<T>, LineSegment<T>>
	intersect(LineSegment<T> const& other) const;
	
	/**
	 * returns p0 + u
	 */
	Vec2d<T> get_end() const;
	
	/**
	 * Returns p0
	 */
	Vec2d<T> get_start() const;

	Vec2d<T> get_vector() const;

    private:
	//p(s) = p0 + su
	Vec2d<T> p0;
	Vec2d<T> u;    // u = p1 - p0
    
    };

    /**
     * Checks if a <= b <= c
     */
    template <typename T>
    inline bool within(T a, T b, T c);
}

#include "line_segment.tcc"

#endif
