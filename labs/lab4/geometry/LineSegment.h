#ifndef LINE_SEG
#define LINE_SEG

#include <variant>
#include <algorithm>

#include "point.h"

template<typename T>
class LineSegment
{
public:
    LineSegment(point<T> p0, point<T> p1)
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

    //T segment_distance(LineSegment<T> const& other) const;

    /**
     * Calculates the point on the line that is closest to the given pt
     *
     * pt    : The point to measure distance to
     * return: The closest point on this line
     */
    point<T> closest_point(point<T> const& pt) const;

    bool contains(point<T> const& pt) const;

    /*
     * Returns the point where this Line and other intersects If they
     * don't intersect then return point(std::numeric_limits<T>::min())
     *
     * There are three cases, the segments are not intersecting, the
     * segments are intersecting in one point and the segments overlap in
     * multiple points.
     *
     * Given Lines 
     * L1(t) = p + t * U
     * L2(s) = q + s * V
     *
     * If U x V == 0 then the lines are parallel since cross-product
     * between two points is defined as the determinant of said
     * points. The determinant is a measurement of area between the
     * vectors. The only case when there is no area in the square that
     * they form is when they are parallel
     *
     *** Parallel
     *
     * Can check if the lines are overlapping with the following condition
     * (q - p) x U == 0
     *
     * If they are not overlapping then there is no way that the line
     * segmnts could overlap, return {}. If they are we need to determine
     * the line segment that the overlapping creates. This can be done by
     * determining either t or s and thus the start and end point of the
     * new line segment.
     *
     * t0 = (q - p)*U / U*U 
     * t1 = t0 + V*U / V*V 
     *
     * where * is the dot product. Six different cases exist for how the
     * two line segments can be aligned. These cases are handled through
     * min/max statements thus eliminating the need for numerous if
     * statements.
     *
     * Finally p_start and p_end are calculated using t_min and t_max:
     * p_start = p + t_min * U
     * p_end = p + t_max * U
     *
     * if p_start == p_end then the intersection only occurs in one spot
     * and thus the function returns said point only. Otherwise it returns
     * the resulting line segment.
     *
     *** Not parallel
     *
     * The intersection point is defined by the constants t, s that
     * solves the following equation:
     * L1(t) = L2(s) =>
     * p + t * U = q + s * V
     * 
     * We get the constant t on Line L1:
     *t = (q - p) x V / U x V 
     *
     * Then, to be able to check if the intersection is within the
     * limits of both line segments we get the constant s on line
     * L2. This is optimized by reusing calculations from the
     * expression above. This is done by rewriting the expressin as
     * follows:
     * s = (( (p - q) x U ) / V x U => / A x B = -B x A / =>
     * s = ( -(q - p) x U ) / -U x V =>
     * s = ( (q - p) x U ) / U x V
     *
     * Now we can check if the intersection point is on both line
     * segments by checking if s and t are within the interval [0, 1]
     *
     * Then we obtain the actual intersection point from the following:
     * p_inter = p + t * U
     *
     * other : The line to check for intersection with
     * return: The intersection point. If there is non then return point with
     *         std::numeric_limits<T>::min() as its values
     */
    std::variant<std::monostate, point<T>, LineSegment<T>>
     intersection(LineSegment<T> const& other) const;
    
    //p(s) = p0 + su
    point<T> p0;
    point<T> u;    // u = p1 - p0
    
};


/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/

template <typename T>
bool LineSegment<T>::operator==(LineSegment<T> const& other) const
{
    return this->p0 == other.p0 && this->u == other.u;
}

template <typename T>
bool LineSegment<T>::operator!=(LineSegment<T> const& other) const
{
    return ! (*this == other);
}

template <typename T>
bool LineSegment<T>::contains(point<T> const& pt) const
{
    T t { dot( (pt - p0), u) / dot(u, u) };
    return t >= 0 && t <= 1;
}

/**
 * The closes distance between a line and a point is the tangent to
 * the line that passes through the point.
 *
 * P: point on the line where tangent to the line intersects both P and pt
 * L1(t) = q + t * U
 *
 * A vector X can be written as X = XL + Xort where XL is the part of
 * the vector that is parallel to the line and Xort is the part of X
 * that is orthogonal to the line. Xort is the orthogonal projection
 * onto the line.
 *
 * XL   = q + c * u
 * Xort = X - XL
 * c = U*X / U*U
 *
 * If 0 <= c <= 1 then the point is on the line segment. If it is not
 * then one of the endpoints of the line segment is the closest point to x
 *
 *
 */
template <typename T>
point<T> LineSegment<T>::closest_point(point<T> const& x) const
{
    point<T> u = this->u;
    point<T> q = this->p0;

    T c = dot(u, x) / dot(u, u);

    //If 0 <= c <= 1 then the point is on the line segment
    if (c <= 1 && c >= 0)
    {
	return u * c;
    }

    //Otherwise one of the line segments endpoints is closest
    point<T> v1{q - x};
    point<T> v2{(q + u) - x};

    if (dot(v1, v1) > dot(v2, v2))
    {
	return q;
    }
    return q + u;       
}

template <typename T>
std::variant<std::monostate, point<T>, LineSegment<T>>
LineSegment<T>::intersection(LineSegment<T> const& other) const
{
    point<T> u = this->u;
    point<T> p = this->p0;
    
    point<T> v = other.u;
    point<T> q = other.p0;
    
    //t = ( (q - p) x V ) / U x V
    point<T> qp = q - p;
    T uv = cross(u, v);

    T u2 = dot(u, u);
    T v2 = dot(v, v);
    
    //If u2 == 0 then other is a point, not a line
    if (std::abs(u2) < 1e-6)
    {
    	if (other.contains(p))
    	{
    	    return p;
    	}
    	return {};
    }
    //If v2 == 0 then this is a point, not a line
    if (std::abs(v2) < 1e-6)
    {
    	if (this->contains(q))
    	{
    	    return q;
    	}
    	return {};
    }

    //If U x V == 0 then the segments are parallel
    if (std::abs(uv) < 1e-6 ) 
    {
	//IF (q-p) x u == 0 then the lines are overlapping
	if ( std::abs( cross(qp, u) ) < 1e-6 )
	{	    
	    T t0 = dot(qp, u) / u2;
	    T t1 = t0 + dot(v, u) / u2;

	    T t_max = std::min( (T) 1, std::max(t0, t1));
	    T t_min = std::max( (T) 0, std::min(t0, t1));

	    //If t_min and t_max belongs to the interval [0, 1] then
	    //the line segments overlap otherwise there is no solution
	    if (t_max <= 1 && t_max >= 0 && t_min <= 1 && t_min >= 0)
	    {
		point<T> p_start(p + t_min * u);
		point<T> p_end(p + t_max * u);

		//If p_start and p_end are the same then the lines
		//only intersect in one point, return that point
		if (p_start == p_end)
		{
		    return p_start;
		}

		return LineSegment<T>(p_start, p_end);
	    }
	}
    }
    //Else they intersect in one point
    else
    {
	T t = cross(qp, v) / uv;

	//Can reuse calculations from t by using the following properties:
	// s = (( (p - q) x U ) / V x U => / A x B = -B x A / =>
	// s = ( -(q - p) x U ) / -U x V =>
	// s = ( (q - p) x U ) / U x V
	T s = cross(qp, u) / uv;

	//Check if s and t are valid, if not then they do not intersect
	if (t <= 1 && t >= 0 && s <= 1 && s >= 0)
	{
	    return point<T>{ p + (t * u) };
	}
    }

    return {};
}

#endif
