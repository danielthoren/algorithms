
#include <algorithm>

#ifndef LINE_SEG
#error 'line_segment.tcc' is not supposed to be included directly. Include 'line_segment.h' instead.
#endif

template <typename T>
bool dalg::LineSegment<T>::operator==(dalg::LineSegment<T> const& other) const
{
    return this->p0 == other.p0 && this->u == other.u;
}

template <typename T>
bool dalg::LineSegment<T>::operator!=(dalg::LineSegment<T> const& other) const
{
    return ! (*this == other);
}

template <typename T>
void dalg::LineSegment<T>::operator=(dalg::LineSegment<T> const& other)
{
    p0 = other.p0;
    u = other.u;
}

template <typename T>
bool dalg::LineSegment<T>::on_line(dalg::Vec2d<T> const& pt) const
{
    //This is a point, check if both points are the same
    if (u.x == 0 && u.y == 0)
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
bool dalg::LineSegment<T>::on_segment(dalg::Vec2d<T> const& pt) const
{   
    if (on_line(pt))
    {
	return within(p0.x, pt.x, (p0+u).x) ||
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
dalg::Vec2d<T> dalg::LineSegment<T>::closest_point(dalg::Vec2d<T> const& x) const
{
    //Move coordinate system if the line does not go through origo
    dalg::Vec2d<T> xt = x - p0;

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
	dalg::Vec2d<T> res = c * u + p0;
	return res;
    }

    //Otherwise one of the line segments endpoints is closest
    dalg::Vec2d<T> v1{p0 - x};
    dalg::Vec2d<T> v2{(p0 + u) - x};

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
std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>> dalg::LineSegment<T>::closest_points(dalg::LineSegment<T> const& lseg) const
{    
    dalg::Vec2d<T> p_res      { closest_point(lseg.p0) };
    dalg::Vec2d<T> u_res      { closest_point(lseg.p0 + lseg.u) };
    dalg::Vec2d<T> p_res_other{ lseg.closest_point(p0) };
    dalg::Vec2d<T> u_res_other{ lseg.closest_point(p0 + u) };

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
template <typename T>
std::variant<std::monostate, dalg::Vec2d<T>, dalg::LineSegment<T>>
dalg::LineSegment<T>::intersect(dalg::LineSegment<T> const& other) const
{
    dalg::Vec2d<T> const& u = this->u;
    dalg::Vec2d<T> const& p = this->p0;
    
    dalg::Vec2d<T> const& v = other.u;
    dalg::Vec2d<T> const& q = other.p0;
    
    //t = ( (q - p) x V ) / U x V
    dalg::Vec2d<T> qp = q - p;
    T uv = cross(u, v);

    T u2 = dot(u, u);
    T v2 = dot(v, v);
    
    //If u2 == 0 then other is a point, not a line
    if (std::abs(u2) < 1e-6)
    {
    	if (other.on_segment(p))
    	{
    	    return p;
    	}
    	return {};
    }
    //If v2 == 0 then this is a point, not a line
    if (std::abs(v2) < 1e-6)
    {
    	if (this->on_segment(q))
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
		dalg::Vec2d<T> p_start(p + t_min * u);
		dalg::Vec2d<T> p_end(p + t_max * u);

		//If p_start and p_end are the same then the lines
		//only intersect in one point, return that point
		if (p_start == p_end)
		{
		    return p_start;
		}

		return dalg::LineSegment<T>(p_start, p_end);
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
	    return dalg::Vec2d<T>{ p + (t * u) };
	}
    }

    return {};
}

template<typename T>
dalg::Vec2d<T> dalg::LineSegment<T>::get_end() const
{
    return p0 + u;
}

template<typename T>
dalg::Vec2d<T> dalg::LineSegment<T>::get_start() const
{
    return p0;
}

template<typename T>
dalg::Vec2d<T> dalg::LineSegment<T>::get_vector() const
{
    return u;
}
