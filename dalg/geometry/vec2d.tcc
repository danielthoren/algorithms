
#include <cmath>

#ifndef VEC_2D
#error 'vec2d.tcc' is not supposed to be included directly. Include 'vec2d.h' instead.
#endif

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
    return x == other.x && y == other.y;
}

template <typename T>
bool dalg::Vec2d<T>::operator!=(dalg::Vec2d<T> const& other) const
{
    return !( *this == other );
}

template <typename T>
T dalg::Vec2d<T>::distance(dalg::Vec2d<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return std::sqrt( std::pow(x_dist, 2) + std::pow(y_dist, 2) );
}

template <typename T>
dalg::Vec2d<T> dalg::Vec2d<T>::distance_vec(dalg::Vec2d<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return dalg::Vec2d<T>{x_dist, y_dist};
}

template <typename T>
double dalg::Vec2d<T>::length() const
{
    return std::sqrt( dot(*this, *this) );
}

/************************/
/* Non-Member functions */
/************************/

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
