#include <cmath>

#ifndef DALG_COLLISION
#error 'collision.tcc' is not supposed to be included directly. Include 'collision.h' instead.
#endif

namespace dalg
{
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
}
