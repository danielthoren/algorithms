
#include <cmath>

#ifndef POINT_2D
#error 'point.tcc' is not supposed to be included directly. Include 'point.h' instead.
#endif

template <typename T>
Point<T> Point<T>::operator+(Point<T> const& other) const
{
    Point<T> tmp{*this};
    tmp += other;
    return tmp;
}

template <typename T>
Point<T>& Point<T>::operator+=(Point<T> const& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
Point<T> Point<T>::operator-(Point<T> const& other) const
{
    Point<T> tmp{*this};
    tmp -= other;
    return tmp;
}

template <typename T>
Point<T>& Point<T>::operator-=(Point<T> const& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template <typename T>
Point<T>& Point<T>::operator=(Point const& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

template <typename T>
bool Point<T>::operator==(Point<T> const& other) const
{
    return x == other.x && y == other.y;
}

template <typename T>
bool Point<T>::operator!=(Point<T> const& other) const
{
    return !( *this == other );
}

template <typename T>
T Point<T>::distance(Point<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return std::sqrt( std::pow(x_dist, 2) + std::pow(y_dist, 2) );
}

template <typename T>
Point<T> Point<T>::distance_vec(Point<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return Point<T>{x_dist, y_dist};
}

template <typename T>
double Point<T>::length() const
{
    return std::sqrt( dot(*this, *this) );
}

/************************/
/* Non-Member functions */
/************************/

template <typename T>
Point<T> operator*(T scalar, Point<T> const& pt)
{
    return Point<T>{pt.x * scalar, pt.y * scalar};
}

template <typename T>
Point<T> operator*(Point<T> const& pt, T scalar)
{
    return Point<T>{pt.x * scalar, pt.y * scalar};
}
