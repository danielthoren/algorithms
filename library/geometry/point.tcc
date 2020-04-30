
#include <cmath>

template <typename T>
point<T> point<T>::operator+(point<T> const& other) const
{
    point<T> tmp{*this};
    tmp += other;
    return tmp;
}

template <typename T>
point<T>& point<T>::operator+=(point<T> const& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
point<T> point<T>::operator-(point<T> const& other) const
{
    point<T> tmp{*this};
    tmp -= other;
    return tmp;
}

template <typename T>
point<T>& point<T>::operator-=(point<T> const& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template <typename T>
point<T>& point<T>::operator=(point const& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

template <typename T>
bool point<T>::operator==(point<T> const& other) const
{
    return x == other.x && y == other.y;
}

template <typename T>
bool point<T>::operator!=(point<T> const& other) const
{
    return !( *this == other );
}

template <typename T>
T point<T>::distance(point<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return std::sqrt( std::pow(x_dist, 2) + std::pow(y_dist, 2) );
}

template <typename T>
point<T> point<T>::distance_vec(point<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return point<T>{x_dist, y_dist};
}

template <typename T>
double point<T>::length() const
{
    return std::sqrt( dot(*this, *this) );
}

/************************/
/* Non-Member functions */
/************************/

template <typename T>
point<T> operator*(T scalar, point<T> const& pt)
{
    return point<T>{pt.x * scalar, pt.y * scalar};
}

template <typename T>
point<T> operator*(point<T> const& pt, T scalar)
{
    return point<T>{pt.x * scalar, pt.y * scalar};
}
