
#ifndef POINT_2D
#define POINT_2D

#include <iostream>
#include <cmath>

namespace dalg
{

    /**
     * Author: Daniel Thorén
     *
     * Class representing a 2-dimensional point. The class supports all
     * expected operations including calculating gcd and lcm.
     */
    template <typename T>
    class Point
    {
    public:
	Point(T x = 0, T y = 0, T prec = 0.05) :
	    x{x}, y{y}, prec{prec}
	    {}
    
	Point(Point const& pt, T prec = 0.05) :
	    x{pt.x}, y{pt.y}, prec{prec}
	    {}

	~Point() = default;

	Point operator+(Point const& other) const;
	Point& operator+=(Point const& other);

	Point operator-(Point const& other) const;
	Point& operator-=(Point const& other);

	Point& operator=(Point const& other);

	bool operator==(Point const& other) const;
	bool operator!=(Point const& other) const;
    
	/*
	 * Distance calculated using pythagorean theorem
	 */
	T distance(Point const& other) const;
	Point distance_vec(Point const& other) const;
	//double angle(Point const&other) const;

	double length() const;
    
	T x;
	T y;
	T prec;
    };

    template<typename T>
    Point<T> operator*(T scalar, Point<T> const& pt);

    template<typename T>
    Point<T> operator*(Point<T> const& pt, T scalar);

    template<typename T>
    std::ostream& operator<<(std::ostream& os, Point<T> const& pt)
    {
	os << "(" << pt.x << ", " << pt.y << ")";
	return os;
    }

/*
 * Returns the cross product of the two Points which is defined as
 * the Determinant of the two Points. 
 *(The area of the surface that the two vectors
 * create when drawing a square with two of each of the vectors)
 */
    template<typename T>
    T cross(Point<T> const& u, Point<T> const& v)
    {
	return u.x * v.y - u.y * v.x;
    }

    template<typename T>
    T dot(Point<T> const& u, Point<T> const& v)
    {
	return u.x * v.x + u.y * v.y;
    }

/************************/
/* Non-Member functions */
/************************/

/**
 * Scalar multiplication between two Points
 */
    template <typename T>
    Point<T> operator*(T scalar, Point<T> const& pt);

    template <typename T>
    Point<T> operator*(Point<T> const& pt, T scalar);
}

#include "point.tcc"

#endif
