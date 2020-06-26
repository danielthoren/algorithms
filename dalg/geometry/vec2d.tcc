
#include <cmath>

#ifndef VEC_2D
#error 'vec2d.tcc' is not supposed to be included directly. Include 'vec2d.h' instead.
#endif

namespace dalg
{

    template <typename T>
    bool Vec2d<T>::equals(Vec2d<T> const& other, std::true_type) const
    {
	p_type precision = get_pref_prec(prec, other.prec);
	return std::abs(x - other.x) <= precision && std::abs(y - other.y) <= precision;
    }

    template <typename T>
    bool Vec2d<T>::equals(Vec2d<T> const& other, std::false_type) const
    {
	return x == other.x && y == other.y;
    }

    template <typename T>
    Vec2d<T> Vec2d<T>::operator+(Vec2d<T> const& other) const
    {
	Vec2d<T> tmp{*this};
	tmp += other;
	return tmp;
    }

    template <typename T>
    Vec2d<T>& Vec2d<T>::operator+=(Vec2d<T> const& other)
    {
	x += other.x;
	y += other.y;
	return *this;
    }

    template <typename T>
    Vec2d<T> Vec2d<T>::operator-(Vec2d<T> const& other) const
    {
	Vec2d<T> tmp{*this};
	tmp -= other;
	return tmp;
    }

    template <typename T>
    Vec2d<T>& Vec2d<T>::operator-=(Vec2d<T> const& other)
    {
	x -= other.x;
	y -= other.y;
	return *this;
    }

    template <typename T>
    Vec2d<T>& Vec2d<T>::operator*=(T scalar)
    {
	*this = *this * scalar;
	return *this;
    }

    template <typename T>
    Vec2d<T>& Vec2d<T>::operator/=(T scalar)
    {
	*this = *this / scalar;
	return *this;
    }

    template <typename T>
    bool Vec2d<T>::operator==(Vec2d<T> const& other) const
    {
	return equals(other, std::is_floating_point<T>{});
    }

    template <typename T>
    bool Vec2d<T>::operator!=(Vec2d<T> const& other) const
    {
	return !( *this == other );
    }

    template <typename T>
    double Vec2d<T>::distance(Vec2d<T> const& other) const
    {
	return std::abs( (other - *this).length() );
    }

    template <typename T>
    double Vec2d<T>::length() const
    {
	return std::sqrt( dot(*this, *this) );
    }

/************************/
/* Non-Member functions */
/************************/

    template<typename T>
    T cross(Vec2d<T> const& u, Vec2d<T> const& v)
    {
	return u.x * v.y - u.y * v.x;
    }

    template<typename T>
    T dot(Vec2d<T> const& u, Vec2d<T> const& v)
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
    double rad_angle(Vec2d<T> const& v1, Vec2d<T> const& v2)
    {
	return std::acos( dot(v1, v2) / (v1.length() * v2.length()) );
    }

    template <typename T>
    double angle(Vec2d<T> const& v1, Vec2d<T> const& v2)
    {
	return rad_angle(v1, v2) * (180.0 / PI);
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
    Vec2d<FL> project(Vec2d<T> const& v, Vec2d<T> const& s)
    {
	FL div = static_cast<FL>( dot(v, s) ) / static_cast<FL>( dot(s, s) );
    
	Vec2d<FL> projection{ static_cast<FL>(s.x),
			      static_cast<FL>(s.y),
			      static_cast<FL>(s.prec) };
    
	projection = projection * div;

	return projection;
    }

    template <typename T>
    Vec2d<T> operator*(T scalar, Vec2d<T> const& pt)
    {
	return Vec2d<T>{pt.x * scalar, pt.y * scalar};
    }

    template <typename T>
    Vec2d<T> operator*(Vec2d<T> const& pt, T scalar)
    {
	return Vec2d<T>{pt.x * scalar, pt.y * scalar};
    }

    template <typename T>
    Vec2d<T> operator/(T scalar, Vec2d<T> const& pt)
    {
	return Vec2d<T>{pt.x / scalar, pt.y / scalar};
    }

    template <typename T>
    Vec2d<T> operator/(Vec2d<T> const& pt, T scalar)
    {
	return Vec2d<T>{pt.x / scalar, pt.y / scalar};
    }

    template <typename T>
    bool collinear(Vec2d<T> const& a,
		   Vec2d<T> const& b,
		   Vec2d<T> const& c)
    {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) < a.prec;
    }

    template <typename T>
    bool collinear(std::vector<Vec2d<T>> const& points)
    {
	if (points.size() < 3)
	    return true;

	unsigned p1{0};
	unsigned p2{1};
	unsigned p3{2};
	for (int i{2}; i < points.size(); i++)
	{
	    if (!collinear(points[p1], points[p2], points[p3]))
		return false;

	    ++p1;
	    ++p2;
	    ++p3;
	}

	return true;
    }

}
