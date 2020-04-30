#ifndef LINE_
#define LINE_

#include "point.h"

#include <limits>

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
    Line(Point<T> p0, Point<T> p1)
	: p0{p0}, u{p1 - p0}
	{}
    
    Line(T x0, T y0, T x1, T y1)
	: Line({x0, y0}, {x1, y1 })
	{}

    /**
     * Checks if the Lines are equal (parallel and has the same points)
     */
    bool operator==(Line<T> const& other) const;
    bool operator!=(Line<T> const& other) const;

    bool is_parallel(Line<T> const& other) const;

    Point<T> orthogonal_projection(Point<T> const& pt) const;

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
    Point<T> intersection(Line<T> const& other) const;

protected:
    //p(s) = p0 + su
    Point<T> p0;
    Point<T> u;    // u = p1 - p0
};

/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/

template <typename T>
bool Line<T>::is_parallel(Line<T> const& other) const
{
    return u.determinant(other.u) == 0;
}


template <typename T>
bool Line<T>::operator==(Line<T> const& other) const
{
    return is_parallel(other) && u.determinant(p0 - other.p0) == 0;
}

template <typename T>
bool Line<T>::operator!=(Line<T> const& other) const
{
    return ! (*this == other);
}

template <typename T>
Point<T> Line<T>::orthogonal_projection(Point<T> const& pt) const
{
    return ((pt * u) / (u * u)) * u;
}


template <typename T>
Point<T> Line<T>::intersection(Line<T> const& other) const
{
    T t = other.u.determinant( (other.p0 - p0) ) / other.u.determinant(u);

    //No solution
    if (t == 0)
    {
	return Point<T>(std::numeric_limits<T>::min(),
			std::numeric_limits<T>::min());
    }

    Point<T> inter{ p0 + (t * u) };
    return inter;
}   

#endif
