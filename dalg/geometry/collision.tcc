#include <cmath>

#ifndef DALG_COLLISION
#error 'collision.tcc' is not supposed to be included directly. Include 'collision.h' instead.
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
     * a^2 + h^2 = r0^2 
     * b^2 + h^2 = r1^2
     *
     * Set d = a + b and solve for a:
     *
     * a = (r0^2 - r1^2 + d^2) / 2*(a + b)
     *
     * h = sqrt( r0^2 - a^2 )
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
    inline std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>>, Circle<T> >
    intersect(Circle<T> const& c0, Circle<T> const& c1)
    {
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

	Vec2d<T> p30 { p2.x + h * (y1 - y0), p2.y - h * (x1 - x0) / d };

	if ( std::abs(a - r0) < c0.center.prec )
	{
	    return p30;
	}

	Vec2d<T> p31 { p2.x - h * (y1 - y0), p2.y + h * (x1 - x0) / d };

	return std::pair<Vec2d<T>, Vec2d<T>>{p30, p31};
    }

    template <typename T>
    inline std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>> >
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
    
}
