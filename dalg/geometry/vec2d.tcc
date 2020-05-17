
#include <cmath>

#ifndef VEC_2D
#error 'vec2d.tcc' is not supposed to be included directly. Include 'vec2d.h' instead.
#endif

template <typename T>
bool dalg::Vec2d<T>::equals(dalg::Vec2d<T> const& other, std::true_type) const
{
    return std::abs(x - other.x) < prec && std::abs(y - other.y) < prec;
}

template <typename T>
bool dalg::Vec2d<T>::equals(dalg::Vec2d<T> const& other, std::false_type) const
{
    return x == other.x && y == other.y;
}

template <typename T>
dalg::Vec2d<T> dalg::Vec2d<T>::operator+(dalg::Vec2d<T> const& other) const
{
    dalg::Vec2d<T> tmp{*this};
    tmp += other;
    return tmp;
}

template <typename T>
dalg::Vec2d<T>& dalg::Vec2d<T>::operator+=(dalg::Vec2d<T> const& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
dalg::Vec2d<T> dalg::Vec2d<T>::operator-(dalg::Vec2d<T> const& other) const
{
    dalg::Vec2d<T> tmp{*this};
    tmp -= other;
    return tmp;
}

template <typename T>
dalg::Vec2d<T>& dalg::Vec2d<T>::operator-=(dalg::Vec2d<T> const& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template <typename T>
dalg::Vec2d<T>& dalg::Vec2d<T>::operator*=(T scalar)
{
    *this = *this * scalar;
    return *this;
}

template <typename T>
dalg::Vec2d<T>& dalg::Vec2d<T>::operator=(dalg::Vec2d<T> const& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

template <typename T>
bool dalg::Vec2d<T>::operator==(dalg::Vec2d<T> const& other) const
{
    return equals(other, std::is_floating_point<T>{});
}

template <typename T>
bool dalg::Vec2d<T>::operator!=(dalg::Vec2d<T> const& other) const
{
    return !( *this == other );
}

template <typename T>
double dalg::Vec2d<T>::distance(dalg::Vec2d<T> const& other) const
{
    return std::abs( (other - *this).length() );
}

template <typename T>
double dalg::Vec2d<T>::length() const
{
    return std::sqrt( dot(*this, *this) );
}

/************************/
/* Non-Member functions */
/************************/

template<typename T>
T dalg::cross(dalg::Vec2d<T> const& u, dalg::Vec2d<T> const& v)
{
    return u.x * v.y - u.y * v.x;
}

template<typename T>
T dalg::dot(dalg::Vec2d<T> const& u, dalg::Vec2d<T> const& v)
{
    return u.x * v.x + u.y * v.y;
}

/**
 * Calculates the angle using pythagoras
 *      /|
 *     / |
 *    /  | b
 *   /   |
 *  /____|
 *    a
 * angle = acos(b/a) * 2
 */
template <typename T>
double dalg::rad_angle(Vec2d<T> const& v1, Vec2d<T> const& v2)
{
    return std::acos( dot(v1, v2) / (v1.length() * v2.length()) );
}

template <typename T>
double dalg::angle(Vec2d<T> const& v1, Vec2d<T> const& v2)
{
    return rad_angle(v1, v2) * (180.0 / dalg::Vec2d<T>::PI);
}

/**
 * Projects this line segment onto the given line using orthogonal
 * projection accoring to the following formula:
 *
 * proj(V) = ( (V dot S) / (S dot S) ) * S
 *
 * a     : The line to project
 * b     : The line to project a on to
 * return: The projection onto the given line
 */
template <typename T, typename FL>
dalg::Vec2d<FL> dalg::project(dalg::Vec2d<T> const& v, dalg::Vec2d<T> const& s)
{
    FL div = static_cast<FL>( dot(v, s) ) / static_cast<FL>( dot(s, s) );
    
    dalg::Vec2d<FL> projection{ static_cast<FL>(s.x),
				static_cast<FL>(s.y),
				static_cast<FL>(s.prec) };
    
    projection = projection * div;

    return projection;
}

template <typename T>
dalg::Vec2d<T> dalg::operator*(T scalar, dalg::Vec2d<T> const& pt)
{
    return dalg::Vec2d<T>{pt.x * scalar, pt.y * scalar};
}

template <typename T>
dalg::Vec2d<T> dalg::operator*(dalg::Vec2d<T> const& pt, T scalar)
{
    return dalg::Vec2d<T>{pt.x * scalar, pt.y * scalar};
}

template <typename T>
dalg::Vec2d<T> dalg::operator/(T scalar, dalg::Vec2d<T> const& pt)
{
    return dalg::Vec2d<T>{pt.x / scalar, pt.y / scalar};
}

template <typename T>
dalg::Vec2d<T> dalg::operator/(dalg::Vec2d<T> const& pt, T scalar)
{
    return dalg::Vec2d<T>{pt.x / scalar, pt.y / scalar};
}

template <typename T>
bool dalg::collinear(dalg::Vec2d<T> const& a,
		     dalg::Vec2d<T> const& b,
		     dalg::Vec2d<T> const& c)
{
  return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) < a.prec;
}

template <typename T>
bool dalg::collinear(std::vector<dalg::Vec2d<T>> const& points)
{
  if (points.size() < 3)
    return true;

  unsigned p1{0};
  unsigned p2{1};
  unsigned p3{2};
  for (int i{2}; i < points.size(); i++)
    {
      if (!dalg::collinear(points[p1], points[p2], points[p3]))
	return false;

      ++p1;
      ++p2;
      ++p3;
    }

  return true;
}

template <typename T>
inline bool within(T a, T b, T c)
{
  return
    (a <= b && b <= c) ||
    (c <= b && b <= a);
}

template <typename T>
bool dalg::on_line(dalg::Vec2d<T> const& p,
		   dalg::Vec2d<T> const& u,
		   dalg::Vec2d<T> const& point)
{
    //This is a point, check if both points are the same
  if (p == point || (p + u) == point)
  {
      return true;
  }
    
  T t { dot( (point - p), u) / dot(u, u) };
  return (p + u * t) == point;

  return dalg::collinear(p, p + u, point) &&
    ((within(p.x, point.x, (p + u).x)) ||
      within(p.y, point.y, (p + u).y));
    
}

/*
 * Returns the point where line segments intersects. Returns line if the lines
 * overlap. 
 *
 * The line segments is defined as follows:
 *
 * L1(x) = p + u * x : x = 1
 * L2(x) = q + v * x : x = 1
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
 * return: The intersection point or line
 */
template <typename T>
std::variant<std::monostate, dalg::Vec2d<T>, std::pair<dalg::Vec2d<T>, dalg::Vec2d<T>>>
	     dalg::line_seg_intersection(dalg::Vec2d<T> const& p,
					 dalg::Vec2d<T> const& u,
					 dalg::Vec2d<T> const& q,
					 dalg::Vec2d<T> const& v)
{    
  //t = ( (q - p) x V ) / U x V
  dalg::Vec2d<T> qp = q - p;
  T uv = cross(u, v);

  T u2 = dot(u, u);
  T v2 = dot(v, v);
    
  //If u2 == 0 then other is a point, not a line
  if (std::abs(u2) < 1e-6)
    {
      if ( on_line(q, q+v, p) )
    	{
	  return p;
    	}
      return {};
    }
  //If v2 == 0 then this is a point, not a line
  if (std::abs(v2) < 1e-6)
    {
      if ( on_line(p, p+u, q) )
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

	      return std::pair{p_start, p_end - p_start};
	      //return dalg::LineSegment<T>(p_start, p_end);
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
