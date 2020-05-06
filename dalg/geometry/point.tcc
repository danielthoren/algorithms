
#include <cmath>

#ifndef POINT_2D
#error 'point.tcc' is not supposed to be included directly. Include 'point.h' instead.
#endif

template <typename T>
dalg::Point<T> dalg::Point<T>::operator+(dalg::Point<T> const& other) const
{
    dalg::Point<T> tmp{*this};
    tmp += other;
    return tmp;
}

template <typename T>
dalg::Point<T>& dalg::Point<T>::operator+=(dalg::Point<T> const& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
dalg::Point<T> dalg::Point<T>::operator-(dalg::Point<T> const& other) const
{
    dalg::Point<T> tmp{*this};
    tmp -= other;
    return tmp;
}

template <typename T>
dalg::Point<T>& dalg::Point<T>::operator-=(dalg::Point<T> const& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template <typename T>
dalg::Point<T>& dalg::Point<T>::operator=(dalg::Point<T> const& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

template <typename T>
bool dalg::Point<T>::operator==(dalg::Point<T> const& other) const
{
    return x == other.x && y == other.y;
}

template <typename T>
bool dalg::Point<T>::operator!=(dalg::Point<T> const& other) const
{
    return !( *this == other );
}

template <typename T>
T dalg::Point<T>::distance(dalg::Point<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return std::sqrt( std::pow(x_dist, 2) + std::pow(y_dist, 2) );
}

template <typename T>
dalg::Point<T> dalg::Point<T>::distance_vec(dalg::Point<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return dalg::Point<T>{x_dist, y_dist};
}

template <typename T>
double dalg::Point<T>::length() const
{
    return std::sqrt( dot(*this, *this) );
}

/************************/
/* Non-Member functions */
/************************/

template <typename T>
dalg::Point<T> dalg::operator*(T scalar, dalg::Point<T> const& pt)
{
    return dalg::Point<T>{pt.x * scalar, pt.y * scalar};
}

template <typename T>
dalg::Point<T> dalg::operator*(dalg::Point<T> const& pt, T scalar)
{
    return dalg::Point<T>{pt.x * scalar, pt.y * scalar};
}
