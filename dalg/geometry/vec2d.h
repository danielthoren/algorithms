
#ifndef VEC_2D
#define VEC_2D

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
    class Vec2d
    {
    public:
	Vec2d(T x = 0, T y = 0, T prec = 0.05) :
	    x{x}, y{y}, prec{prec}
	    {}
    
	Vec2d(Vec2d const& pt, T prec = 0.05) :
	    x{pt.x}, y{pt.y}, prec{prec}
	    {}

	~Vec2d() = default;

	Vec2d operator+(Vec2d const& other) const;
	Vec2d& operator+=(Vec2d const& other);

	Vec2d operator-(Vec2d const& other) const;
	Vec2d& operator-=(Vec2d const& other);

	Vec2d& operator=(Vec2d const& other);

	bool operator==(Vec2d const& other) const;
	bool operator!=(Vec2d const& other) const;
    
	/*
	 * Distance calculated using pythagorean theorem
	 */
	T distance(Vec2d const& other) const;
	Vec2d distance_vec(Vec2d const& other) const;
	//double angle(Point const&other) const;

	double length() const;
    
	T x;
	T y;
	T prec;
    };

    template<typename T>
    Vec2d<T> operator*(T scalar, Vec2d<T> const& pt);

    template<typename T>
    Vec2d<T> operator*(Vec2d<T> const& pt, T scalar);

    template<typename T>
    std::ostream& operator<<(std::ostream& os, Vec2d<T> const& pt)
    {
	os << "(" << pt.x << ", " << pt.y << ")";
	return os;
    }

/*
 * Returns the cross product of the two vectors which is defined as
 * the Determinant of the two vectors. 
 *(The area of the surface that the two vectors
 * create when drawing a square with two of each of the vectors)
 */
    template<typename T>
    T cross(Vec2d<T> const& u, Vec2d<T> const& v)
    {
	return u.x * v.y - u.y * v.x;
    }

    template<typename T>
    T dot(Vec2d<T> const& u, Vec2d<T> const& v)
    {
	return u.x * v.x + u.y * v.y;
    }

/************************/
/* Non-Member functions */
/************************/

/**
 * Scalar multiplication between two Vec2ds
 */
    template <typename T>
    Vec2d<T> operator*(T scalar, Vec2d<T> const& pt);

    template <typename T>
    Vec2d<T> operator*(Vec2d<T> const& pt, T scalar);
}

#include "vec2d.tcc"

#endif
