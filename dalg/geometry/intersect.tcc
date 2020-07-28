#include <cmath>

#ifndef DALG_COLLISION
#error 'intersect.tcc' is not supposed to be included directly. Include 'intersect.h' instead.
#endif

namespace dalg
{
    /**
     * Author: Daniel Thorén
     *
     * Calculates intersection between two Circles. The intersection
     * points are obtained by calculating the angle between c0.centre
     * and each intersection.
     *
     * Firstly both circles are represented as:
     *
     * c0: (x - x0)^2 + (y - y0)^2 = r0^2
     * c1: (x - x1)^2 + (y - y1)^2 = r1^2
     *
     * > Name the center points of c0 and c1 to p0 and p1 respectively
     * > Name the distance between p0 and p1 as ab 
     * > Name the two potential intersection points p3x
     *
     * > Let the middle point where a, b and h meet be named "p2"
     *
     * > Let the distance from p0 to p2 be named "a"
     * > Let the distance from p1 to p2 be named "b"
     *
     * > Let the distance from the vector (p0 - p1) to p3x be named h
     *       _______________    _______________
     *      /               \  /               \
     *     /           p30-->\/                 \ 
     *    /                  /\                  \
     *   /                  / ^\                  \
     *  /                  / h| \                  \
     * |                a |   |  | b                |
     * |      p0-> o<-----|--> <-|---->o <-p1       |
     * |                  |   p2 |                  |
     *  \                  \    /                  /
     *   \                  \  /                  /
     *    \                  \/                  /
     *     \           p31-->/\                 /
     *      \_______________/  \_______________/
     *              
     *
     * This creates a triangle between p0, p3 and the point where h, a
     * and b meets as well as between p1 and the same point:
     *
     *                 p3     p3
     *                /|      |\
     *               / |      | \
     *              /  |      |  \
     *             /   |      |   \
     *            /    |      |    \
     *           /     |      |     \
     *          /      |      |      \
     *       r0/       |<-h-> |       \ r1
     *        /        |      |        \
     *       /         |      |         \
     *      /          |      |          \
     *     /           |      |           \
     *    /            |      |            \
     *   /_____________|      |_____________\
     *  p0      a                    b       p1
     *
     * This give the following equations:
     *
     * a² + h² = r0² 
     * b² + h² = r1²
     *
     * h² = r1² - b² -> 
     * a² + r1² - b² = r0² -> 
     * a² = r0² - r1² + b² (1)
     *
     * Set d = a + b and solve for a:
     *
     * a = (r0² - r1² + d²) / 2*d
     *
     * h = sqrt( r0² - a² )
     *
     * p2 = p0 + a * (p1 - p0) / d
     *
     * x3 = x2 +- h * (y1 - y0) / d
     * y3 = y2 -+ h * (x1 - x0) / d
     *
     * If a == r0 then the circles only intersect in one point, return only p30
     *
     * else return both p30 and p31
     *
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>>, Circle<T> >
    intersect(Circle<T> const& c0, Circle<T> const& c1)
    {
	//Check if the bounding boxes of the circles overlap, if not
	//hten return monostate
	if (!c0.get_aabb().overlap(c1.get_aabb()))
	{
	    return {};
	}
	
	T radius = c0.radius + c1.radius;

	//Translation vector between midpoints
	Vec2d<T> dist_vec{c0.center - c1.center};
	T distance = dist_vec.length();

	//If they are to far away to collide, return monostate
	if (distance * distance > radius * radius)
	{
	    return {};
	}

	//If they completely overlap
	if (distance == 0.0)
	{	    
	    return Circle<T>{c0};
	}

	T x0  { c0.center.x };
	T y0  { c0.center.y };

	T x1  { c1.center.x };
	T y1  { c1.center.y };

	T r0  { c0.radius };
	T r1  { c1.radius };

	T d   { dist_vec.length() };

	T a   { (std::pow(r0, 2) - std::pow(r1, 2) + std::pow(d,2) ) / (2*d) };
	T h  { std::sqrt( std::pow(r0, 2) - std::pow(a, 2) ) };

	Vec2d<T> p2 { c0.center + a * (c1.center - c0.center) / d };

	Vec2d<T> p30 { p2.x + h * (y1 - y0) / d, p2.y - h * (x1 - x0) / d };

	if ( std::abs(a - r0) < c0.center.prec )
	{
	    return p30;
	}

	Vec2d<T> p31 { p2.x - h * (y1 - y0) / d, p2.y + h * (x1 - x0) / d };

	return std::pair<Vec2d<T>, Vec2d<T>>{p30, p31};
    }

    /**
     * Author: Daniel Thorén
     *
     * The following notation for the circle and line is used:
     * 
     * c: (c0 - x0)² + (c1 - x1)² = r² => /parametric form/ => |C - X|² = r²
     * l: X = A + t * B
     *
     * Substitute X in the line into the circle and solv for t:
     *
     * |C - X|² = / X = A + tB / = (C - (A + tB))² = (-tB - (A-C))² = r² =>
     *
     * => |tB|² + 2(A-C)Bt + |A-C|² - r² = 0 =>
     *
     * => t² + 2(A-C)Bt * 1/|B|² + (|A-C|² - r²) * 1/|B|² = 0 =>
     *
     * => t² + 2(A-C)Bt * 1/|B|² + ( (A-C)B * 1/|B|² )² = (r² - |A-C|²) * 1/|B|² + ( (A-C)B * 1/|B|² )² =>
     *
     * => ( t + (A-C)B * 1/|B|² )² = ( (r² - |A-C|²) + (A-C)² ) * |B|² * 1/|B|⁴ =>
     *
     * => t = ( -(A-C)B ± √( (r² - |A-C|²) * |B|² + ((A-C)B)² ) ) * 1/|B|² =>
     *
     * => t = ( -(A-C)B ± √( ((A-C)B)² - |B|² * (|A-C|² - r²) ) ) * 1/|B|²
     * 
     * Thus t is obtained. Using t in the original expression of the
     * line will yield the intersection pint/points.
     *
     *  
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
    intersect(Circle<T> const& c, Line<T> const& l)
    {
	//If the distance between the center of the circle and the
	//closest point on the line is larger than the radius of the
	//circle then they can not intersect
	if ( (project(c.center, l) - c.center).length() > c.radius )
	{
	    return {};
	}
	
	T p = -2 * dot(l.p0 - c.center, l.u);

	T q = std::pow( 2 * dot(l.p0 - c.center, l.u), 2) -
	      4 * std::pow(l.u.length(), 2) *
	      ( std::pow((l.p0 - c.center).length(), 2) - std::pow(c.radius, 2) );
	
	T d = 2 * std::pow(l.u.length(), 2);

	T t1 = ( p + std::sqrt(q) ) / d;
	T t2 = ( p - std::sqrt(q) ) / d;

	Vec2d<T> v1 {l.p0.x + l.u.x * t1, l.p0.y + l.u.y * t1};

	if (t1 - t2 < DEFAULT_PREC)
	{
	    return v1;
	}

	Vec2d<T> v2 {l.p0.x + l.u.x * t2, l.p0.y + l.u.y * t2};

	return std::pair{v1, v2};
    }

    template <typename T>
    inline std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
    intersect(Line<T> const& l, Circle<T> const& c)
    {
	return intersect(c, l);
    }

    /**
     * Author: Daniel Thorén
     *
     * The following notation for the circle and line is used:
     * 
     * c: (c0 - x0)² + (c1 - x1)² = r² => /parametric form/ => |C - X|² = r²
     * l: X = A + t * B
     *
     * This function uses the result from the intersection function
     * between a circle and a line then does a boundry check on the
     * result.
     *  
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
    intersect(Circle<T> const& c, LineSegment<T> const& lseg)
    {
	Line<T> l{lseg.get_start(), lseg.get_end()};
	auto col = intersect<T>(c, l);
	
	if (std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col))
	{
	    std::pair<Vec2d<double>, Vec2d<double>> res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(col);

	    if (lseg.on_segment(res.first))
	    {
		if (lseg.on_segment(res.second))
		{
		    return res;
		}
		return res.first;
	    }
	    if (lseg.on_segment(res.second))
	    {
		return res.second;
	    }
	}
	else if (std::holds_alternative<Vec2d<double>>(col))
	{
	    Vec2d<double> res = std::get<Vec2d<double>>(col);

	    if (lseg.on_line(res))
	    {
		return res;
	    }
	}
	
	return {};
    }

    template <typename T>
    inline std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
    intersect(LineSegment<T> const& l, Circle<T> const& c)
    {
	return intersect(c, l);
    }
    
}
