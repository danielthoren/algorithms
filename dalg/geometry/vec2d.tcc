
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
double dalg::Vec2d<T>::rad_angle(dalg::Vec2d<T> const& other) const
{
    // dalg::Vec2d<T> p = (*this - other) / 2;

    // T a = p.length();
    // T b = (*this - p).length();
    
    // return std::acos(b/a) * 2;

    return std::acos( dot(*this, other) / (length() * other.length()) );
}

template <typename T>
double dalg::Vec2d<T>::distance(dalg::Vec2d<T> const& other) const
{
    return std::abs( (other - *this).length() );
}

template <typename T>
double dalg::Vec2d<T>::angle(dalg::Vec2d<T> const& other) const
{
    return rad_angle(other) * (180.0 / PI);
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
