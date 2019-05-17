#include <cmath>

template <typename T>
Point_2d<T> Point_2d<T>::operator+(Point_2d<T> const& other) const
{
    Point_2d<T> tmp{*this};
    tmp += other;
    return tmp;
}

template <typename T>
Point_2d<T>& Point_2d<T>::operator+=(Point_2d<T> const& other)
{
    x_cord += other.x_cord;
    y_cord += other.y_cord;
    return *this;
}

template <typename T>
Point_2d<T> Point_2d<T>::operator-(Point_2d<T> const& other) const
{
    Point_2d<T> tmp{*this};
    tmp -= other;
    return tmp;
}

template <typename T>
Point_2d<T>& Point_2d<T>::operator-=(Point_2d<T> const& other)
{
    x_cord -= other.x_cord;
    y_cord -= other.y_cord;
    return *this;
}

template <typename T>
Point_2d<T> Point_2d<T>::operator*(Point_2d<T> const& other) const
{
	return scalar(other);
}

template <typename T>
Point_2d<T>& Point_2d<T>::operator=(Point_2d const& other)
{
    x_cord = other.x_cord;
    y_cord = other.y_cord;
    return *this;
}

template <typename T>
bool Point_2d<T>::operator==(Point_2d<T> const& other) const
{
    return x_cord == other.x_cord && y_cord == other.y_cord;	
}

template <typename T>
bool Point_2d<T>::operator!=(Point_2d<T> const& other) const
{
    return !(*this == other);
}

template <typename T>
bool Point_2d<T>::operator<(Point_2d<T> const& other) const
{
    return this->length() < other.length();
}

template <typename T>
bool Point_2d<T>::operator<=(Point_2d<T> const& other) const
{
    return *this < other || *this == other;
}

template <typename T>
bool Point_2d<T>::operator>(Point_2d<T> const& other) const
{
    return !(*this <= other);
}

template <typename T>
bool Point_2d<T>::operator>=(Point_2d<T> const& other) const
{
    return *this > other || *this == other;
}

template <typename T>
T Point_2d<T>::scalar(Point_2d<T> const& other) const
{
    return x_cord * other.x_cord + y_cord * other.y_cord;
}

template <typename T>
T Point_2d<T>::distance(Point_2d<T> const& other) const
{
    T x_dist = std::abs(x_cord - other.x_cord);
    T y_dist = std::abs(y_cord - other.y_cord);

    return std::sqrt(x_dist^2 + y_dist^2);
}

template <typename T>
Point_2d<T> Point_2d<T>::distance_vec(Point_2d<T> const& other) const
{
    T x_dist = std::abs(x_cord - other.x_cord);
    T y_dist = std::abs(y_cord - other.y_cord);

    return Point_2d<T>{x_dist, y_dist};
}

template <typename T>
T Point_2d<T>::determinant(Point_2d<T> const& other) const
{
    return x_cord * other.y_cord - y_cord * other.x_cord;
}

template <typename T>
double Point_2d<T>::length() const
{
    return std::sqrt( std::pow(x_cord, 2) + std::pow(y_cord, 2) );
}

