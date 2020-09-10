
#include "intersect.h"

#include <algorithm>

#ifndef DALG_LINE_SEG
#error 'line_segment.tcc' is not supposed to be included directly. Include 'line_segment.h' instead.
#endif

namespace dalg
{

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
    bool LineSegment<T>::on_line(Vec2d<T> const& pt) const
    {
	//This is a point, check if both points are the same
	if (std::abs(u.x) < prec && std::abs(u.y) < prec)
	{
	    return p0 == pt;
	}
    
	T t { dot( (pt - p0), u) / dot(u, u) };
	return (p0 + u * t) == pt;
    }

    template <typename T>
    inline bool within(T a, T b, T c)
    {
	return (a <= b && b <= c) || (c <= b && b <= a);
    }

    template <typename T>
    bool LineSegment<T>::on_segment(Vec2d<T> const& pt) const
    {   
	if (on_line(pt))
	{
	    return within(p0.x, pt.x, (p0+u).x) &&
		within(p0.y, pt.y, (p0+u).y);
	}
	return false;
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
 * Since the projection is done onto a vector it will be relative
 * origo. Thus to get the correct point on the line the coordinate
 * system needs to be moved so that origo sits at p0 before the
 * ṕrojection is calculated. Then the coordinate system needs to be
 * moved back to get the actual position of the point. Luckily the
 * only position that needs changing is that of x:
 *
 * Xt = X - q
 *
 * Then performing the projection:
 * XL   = q + c * u
 * Xort = Xt - XL
 * c = U*Xt / U*U
 *
 * If 0 <= c <= 1 then the point is on the line segment. If it is not
 * then one of the endpoints of the line segment is the closest point to x
 *
 * Then moving the point back:
 * Rt = c * U
 * R = Rt + q
 *
 * Getting the resulting point R
 *
 * x     : The point to measure distance to
 * return: The resulting point R
 */
    template <typename T>
    Vec2d<T> LineSegment<T>::closest_point(Vec2d<T> const& x) const
    {
	//Move coordinate system if the line does not go through origo
	Vec2d<T> xt = x - p0;

	T u2 = dot(u, u);
    
	//If u2 == 0 then this line is a single point
	if (u2 == 0)
	{
	    return p0;
	}

	//Calculate projection
	T c = dot(u, xt) / u2;

	//If 0 <= c <= 1 then the point is on the line segment
	if (c <= 1 && c >= 0)
	{
	    Vec2d<T> res = c * u + p0;
	    return res;
	}

	//Otherwise one of the line segments endpoints is closest
	Vec2d<T> v1{p0 - x};
	Vec2d<T> v2{(p0 + u) - x};

	if (v1.length() < v2.length())
	{
	    return p0;
	}
	return p0 + u;
    }

/**
 * Functions determines the closest pair of points on the two line
 * segments. This is done by finding the closest point on the other
 * line segment for each of the line segments end points and then
 * calculating the distance. The shortest distance dictates which
 * points are the closest.
 *
 * lseg  : The line segment to calculate the shortest distance to
 * return: The pair of points that are the closest on the given line segments
 *         std::pair<closest on this, closest on lseg>
 */
    template <typename T>
    std::pair<Vec2d<T>, Vec2d<T>> LineSegment<T>::closest_points(LineSegment<T> const& lseg) const
    {
	//If the two segments intersect, closest points is the intersection point
	auto res = intersect(*this, lseg);
	if (std::holds_alternative<Vec2d<T>>(res))
	{
	    Vec2d<T> res_act = std::get<Vec2d<T>>(res);
	    return {res_act, res_act};
	}
	else if (std::holds_alternative<LineSegment<T>>(res))
	{
	    LineSegment<T> res_act = std::get<LineSegment<T>>(res);
	    return {res_act.get_start(), res_act.get_start()};
	}
    
	Vec2d<T> p_res      { closest_point(lseg.p0) };
	Vec2d<T> u_res      { closest_point(lseg.p0 + lseg.u) };
	Vec2d<T> p_res_other{ lseg.closest_point(p0) };
	Vec2d<T> u_res_other{ lseg.closest_point(p0 + u) };

	T p_len       = p_res.distance(lseg.p0);
	T u_len       = u_res.distance(lseg.p0 + lseg.u);
	T p_len_other = p_res_other.distance(p0);
	T u_len_other = u_res_other.distance(p0 + u);
    
	if (p_len <= u_len &&
	    p_len <= p_len_other &&
	    p_len <= u_len_other)
	{
	    return {p_res, lseg.p0};
	}
	else if (
	    u_len <= p_len &&
	    u_len <= p_len_other &&
	    u_len <= u_len_other)
	{
	    return {u_res, lseg.p0 + lseg.u};
	}
	else if (
	    p_len_other <= p_len &&
	    p_len_other <= u_len_other &&
	    p_len_other <= u_len)
	{
	    return {p0, p_res_other};
	}
	else
	{
	    return {p0 + u, u_res_other};
	}
    }

    template<typename T>
    AABB<T> LineSegment<T>::get_aabb() const
    {
	return AABB<T>{p0, p0 + u};
    }
    
    template<typename T>
    Vec2d<T> LineSegment<T>::get_end() const
    {
	return p0 + u;
    }

    template<typename T>
    Vec2d<T> LineSegment<T>::get_start() const
    {
	return p0;
    }

    template<typename T>
    Vec2d<T> LineSegment<T>::get_vec() const
    {
	return u;
    }
}
