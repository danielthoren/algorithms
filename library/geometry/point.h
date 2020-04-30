
#ifndef POINT_2D
#define POINT_2D

#include <iostream>
#include <cmath>

/**
 * Author: Daniel Thorén
 *
 * Class representing a 2-dimensional point. The class supports all
 * expected operations including calculating gcd and lcm.
 */
template <typename T>
class point
{
public:
    point(T x = 0, T y = 0, T prec = 0.05) :
	x{x}, y{y}, prec{prec}
	{}
    
    point(point const& pt, T prec = 0.05) :
	x{pt.x}, y{pt.y}, prec{prec}
	{}

    ~point() = default;

    point operator+(point const& other) const;
    point& operator+=(point const& other);

    point operator-(point const& other) const;
    point& operator-=(point const& other);

    point& operator=(point const& other);

    bool operator==(point const& other) const;
    bool operator!=(point const& other) const;
    
    /*
     * Distance calculated using pythagorean theorem
     */
    T distance(point const& other) const;
    point distance_vec(point const& other) const;
    //double angle(point const&other) const;

    double length() const;
    
    T x;
    T y;
    T prec;
};

template<typename T>
point<T> operator*(T scalar, point<T> const& pt);

template<typename T>
point<T> operator*(point<T> const& pt, T scalar);

template<typename T>
std::ostream& operator<<(std::ostream& os, point<T> const& pt)
{
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}

/*
 * Returns the cross product of the two points which is defined as
 * the Determinant of the two points. 
 *(The area of the surface that the two vectors
 * create when drawing a square with two of each of the vectors)
 */
template<typename T>
T cross(point<T> const& u, point<T> const& v)
{
    return u.x * v.y - u.y * v.x;
}

template<typename T>
T dot(point<T> const& u, point<T> const& v)
{
    return u.x * v.x + u.y * v.y;
}

/************************/
/* Non-Member functions */
/************************/

/**
 * Scalar multiplication between two points
 */
template <typename T>
point<T> operator*(T scalar, point<T> const& pt);

template <typename T>
point<T> operator*(point<T> const& pt, T scalar);

#include "point.tcc"

#endif
