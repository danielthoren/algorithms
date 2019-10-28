
#ifndef POINT_2D
#define POINT_2D

template <typename T>
class Point_2d
{
public:
    Point_2d(T x = 0, T y = 0) :
	x{x}, y{y}
	{}
    
    Point_2d(Point_2d const& pt) :
	x{pt.x}, y{pt.y}
	{}

    ~Point_2d() = default;

    Point_2d operator+(Point_2d const& other) const;
    Point_2d& operator+=(Point_2d const& other);

    Point_2d operator-(Point_2d const& other) const;
    Point_2d& operator-=(Point_2d const& other);

    /*
     * Cross product
     */
    Point_2d<T> operator*(Point_2d const& other) const;

    Point_2d& operator=(Point_2d const& other);

    bool operator==(Point_2d const& other) const;
    bool operator!=(Point_2d const& other) const;
    bool operator<(Point_2d const& other) const;
    bool operator<=(Point_2d const& other) const;
    bool operator>(Point_2d const& other) const;
    bool operator>=(Point_2d const& other) const;

    /*
     * Scalar product
     */
    T scalar(Point_2d const& other) const;

    /*
     * Determinant (The area of the surface that the two vectors
     * create when drawing a square with two of each of the vectors)
     */
    T determinant(Point_2d const& other) const;

    /*
     * Distance calculated using pythagorean theorem
     */
    T distance(Point_2d const& other) const;
    Point_2d distance_vec(Point_2d const& other) const;
    //double angle(Point_2d const&other) const;

    double length() const;
    
    T x;
    T y;
};

/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/

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
    x += other.x;
    y += other.y;
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
    x -= other.x;
    y -= other.y;
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
    x = other.x;
    y = other.y;
    return *this;
}

template <typename T>
bool Point_2d<T>::operator==(Point_2d<T> const& other) const
{
    return x == other.x && y == other.y;	
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
    return x * other.x + y * other.y;
}

template <typename T>
T Point_2d<T>::distance(Point_2d<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return std::sqrt(x_dist^2 + y_dist^2);
}

template <typename T>
Point_2d<T> Point_2d<T>::distance_vec(Point_2d<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return Point_2d<T>{x_dist, y_dist};
}

template <typename T>
T Point_2d<T>::determinant(Point_2d<T> const& other) const
{
    return x * other.y - y * other.x;
}

template <typename T>
double Point_2d<T>::length() const
{
    return std::sqrt( std::pow(x, 2) + std::pow(y, 2) );
}

#endif
