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
	//Check if the bounding boxes of the circle and line_segment
	//overlap, if not hten return monostate
	if (!c.get_aabb().overlap(lseg.get_aabb()))
	{
	    return {};
	}
	
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

    /**
     * Author: Daniel Thorén
     *
     * Handles collisions between two lines. This is done by solving
     * the equation systems:
     *
     * (1):   l1(t) = At + B ->  l1_x(t) = a1 * t + b1
     *                           l1_y(t) = a2 * t + b2
     *
     * (2):   l2(s) = Ps + Q ->  l2_x(s) = p1 * s + q1
     *                           l2_y(s) = p2 * s + q2
     *
     * Where big letters represent 2-dimensional vectors and small
     * letters are variables. An equation system is created by solving
     * each pair of equation for x and y respektively:
     *
     * (3):    (1) & (2) 
     *          -> l1_x(t) = l2_x(s) 
     *           -> a1*t + b1 = p1*s + q1 
     *            -> s = (a1*t + b1 - q1) / p1
     *
     * (4):    (1) & (2) 
     *          -> l1_y(t) = l2_y(s) 
     *           -> a2*t + b2 = p2*s + q2 
     *            -> s = (a2*t + b2 - q2) / p2
     *
     * Set s = s and get:
     *
     * (5):    (3) & (4) 
     *          -> S = S
     *           -> (a1*t + b1 - q1) / p1 = (a2*t + b2 - q1) / p2
     *            -> p2*a1*t + p2*(b1 - q1) = p1*a2*t + p1*(b2 - q2)
     *             -> (p2*a1 - p1*a2)t = p1*(b2 - q2) - p2*(b1 - q1)
     *              -> t = ( p1*(b2 - q2) - p2*(b1 - q1) ) / (p2*a1 - p1*a2)
     *
     * Solve for t then put t into equation (1) to get the point. This
     * can be performed using the determinant in the following manner.
     *
     *                              | p1  (q1 - b1) | 
     *   det(l2.u, l2.p0 - l1.p0) = | p2  (q2 - b2) | = p1(q2 - b2) - p2(q1 - b1)
     *
     *                     | p1  a1 |
     *   det(l2.u, l1.u) = | p2  a2 | = p1*a2 - p2*a1
     *
     * (6):    t = det(l2.u, l2.p0 - l1.p0) / det(l2.u, l1.u)
     *
     *                    | p1  (q1 - b1) |  / | p1  a1 |
     * (7):    (6) -> t = | p2  (q2 - b2) | /  | p2  a2 | 
     *                   = ( p1*(q2 - b2) - p2*(q1 - b1) ) / ( p1*a2 - p2*a1 )
     *                    = -1*( p1*(q2 - b2) - p2*(q1 - b1) ) / -1*( p1*a2 - p2*a1 )
     *                     = ( p1*(b2 - q2) - p2*(b1 - q1) ) / (p2*a1 - p1*a2)
     *
     * (5) <-> (7)
     *
     * Thus equation (6) can be used to easily get t which in turn
     * yeilds the intersection point.
     *
     * l1 : Line 1
     * l2 : Line 2
     *
     * return : monostate         : no intersection
     *          Vec2d             : Only boundry intersection
     *          Line              : l1 and l2 represent the same line
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, Line<T> >
    intersect(Line<T> const& l1, Line<T> const& l2)
    {
	if (l1 == l2)
	{
	    return l1;
	}

	if (collinear(l1.u, l2.u))
	{
	    return {};
	}
	
	T t = cross(l2.u, l2.p0 - l1.p0) / cross(l2.u, l1.u);

	Vec2d<T> inter{ l1.p0 + (t * l1.u) };
	return inter;
    }


/*
 * Returns the point where l1 and l2 intersects If they
 * don't intersect then return monostate
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
    std::variant<std::monostate, Vec2d<T>, LineSegment<T>>
    intersect(LineSegment<T> const& l1, LineSegment<T> const& l2)
    {
	Vec2d<T> const& u = l1.u;
	Vec2d<T> const& p = l1.p0;
    
	Vec2d<T> const& v = l2.u;
	Vec2d<T> const& q = l2.p0;
    
	//t = ( (q - p) x V ) / U x V
	Vec2d<T> qp = q - p;
	T uv = cross(u, v);

	T u2 = dot(u, u);
	T v2 = dot(v, v);
    
	//If u2 == 0 then l2 is a point, not a line
	if (std::abs(u2) < 1e-6)
	{
	    if (l2.on_segment(p))
	    {
		return p;
	    }
	    return {};
	}
	//If v2 == 0 then this is a point, not a line
	if (std::abs(v2) < 1e-6)
	{
	    if (l1.on_segment(q))
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
		    Vec2d<T> p_start(p + t_min * u);
		    Vec2d<T> p_end(p + t_max * u);

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
		return Vec2d<T>{ p + (t * u) };
	    }
	}

	return {};
    }

    
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, LineSegment<T>>
    intersect(Line<T> const& l, LineSegment<T> const& lseg)
    {
	auto res = intersect(l, Line<T>{lseg.p0, lseg.u});

	//If res contains a line then the line segment overlaps with
	//the line, thus return the line semgment
	if ( std::holds_alternative<Line<T>>(res) )
	{
	    return lseg;
	}

	//If res contains a vector and it is on the segment then l and
	//lseg intersects, return point
	if ( std::holds_alternative<Vec2d<T>>(res))
	{
	    Vec2d<T> act = std::get<Vec2d<T>>(res);

	    if (lseg.on_segment(act))
	    {
		return act;
	    }
	}
	
	return {};
    }
    
}
