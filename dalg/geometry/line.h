#ifndef LINE_
#define LINE_

#include "vec2d.h"
#include "utility.h"

#include <limits>

namespace dalg
{

    /**
     * Author: Daniel Thorén
     *
     * Class representing a 2d line. Each endpoint of the line is
     * represented by a 2d point. The class supports various operations.
     */
    template <typename T>
    class Line
    {
    public:
	Line(Vec2d<T> p0, Vec2d<T> u,
	     p_type prec = static_cast<p_type>( DEFAULT_PREC ))
	    : p0{p0}, u{u}, prec{prec}
	    {}
    
	Line(T x0, T y0, T x1, T y1,
	     p_type prec = static_cast<p_type>( DEFAULT_PREC ))
	    : Line({x0, y0}, {x1, y1 }, prec)
	    {}

	/**
	 * Checks if the Lines are equal (parallel and has the same points)
	 */
	bool operator==(Line<T> const& other) const;
	bool operator!=(Line<T> const& other) const;

	bool is_parallel(Line<T> const& other) const;

	/*
	 * Returns the point where this Line and other intersects
	 * If the lines are parallel then return point with
	 * std::numeric_limits<T>::min()
	 *
	 * Given Lines 
	 * L1(t) = p + t * U
	 * L2(s) = q + s * V
	 * 
	 * We get the constant t on Line L1 where the intersection occurs as:
	 * t = (q - p) x V / U x V
	 *
	 * Then we obtain the actual intersection point from the following:
	 * p_inter = p + t * U
	 */
	Vec2d<T> intersection(Line<T> const& other) const;

	//p(s) = p0 + su
	Vec2d<T> p0;
	Vec2d<T> u;    // u = p1 - p0
	p_type prec;
    };

    template <typename T>
    Vec2d<T> project(Vec2d<T> const& pt, Line<T> const& l);

/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/

    template <typename T>
    bool Line<T>::is_parallel(Line<T> const& other) const
    {
	return cross(u, other.u) == 0;
    }


    template <typename T>
    bool Line<T>::operator==(Line<T> const& other) const
    {
	return is_parallel(other) && std::abs( cross(u, p0 - other.p0) ) < prec;
    }

    template <typename T>
    bool Line<T>::operator!=(Line<T> const& other) const
    {
	return ! (*this == other);
    }

    template <typename T>
    Vec2d<T> project(Vec2d<T> const& pt, Line<T> const& l)
    {
	Vec2d<T> pt_t {pt - l.p0};

	Vec2d<T> res{ project(pt_t, l.u) };

	res += l.p0;

	return res;
    }


    template <typename T>
    Vec2d<T> Line<T>::intersection(Line<T> const& other) const
    {
	T t = cross(other.u, (other.p0 - p0) ) / cross(other.u, u);

	//No solution
	if (t == 0)
	{
	    return Vec2d<T>(std::numeric_limits<T>::min(),
			    std::numeric_limits<T>::min());
	}

	Vec2d<T> inter{ p0 + (t * u) };
	return inter;
    }

}

#endif
