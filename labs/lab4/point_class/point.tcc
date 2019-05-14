#include "point.h"

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
    
}

template <typename T>
Point_2d<T>& Point_2d<T>::operator*(Point_2d<T> const& other)
{
    
}

template <typename T>
Point_2d& Point_2d<T>::operator=(Point_2d const& other)
{
    x_cord = other.x_cord;
    y_cord = other.y_cord;
    return *this;
}

template <typename T>
bool Point_2d<T>::operator==(Point_2d<T> const& other)
{
    return x_cord == other.x_cord && y_cord == other.y_cord;	
}

template <typename T>
bool Point_2d<T>::operator!=(Point_2d<T> const& other)
{
    return !(*this == other);
}

template <typename T>
bool Point_2d<T>::operator<(Point_2d<T> const& other)
{
    return *this.length() < other.length();
}

template <typename T>
bool Point_2d<T>::operator<=(Point_2d<T> const& other)
{
    return *this < other || *this == other;
}






