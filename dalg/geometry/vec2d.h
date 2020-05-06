
#ifndef VEC_2D
#define VEC_2D

#include <iostream>
#include <cmath>
#include <type_traits>

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
    private:

	/**
	 * Takes care of comparisons of Integer template types. 
	 */
	bool equals(Vec2d const& other, std::true_type is_floating_point ) const;

	/**
	 * Takes care of comparisons of Floating point template
	 * types. Uses prec vairable in comparison in the following way:
	 *
	 * abs( this.x - other.x ) < prec
	 */
	bool equals(Vec2d const& other, std::false_type is_floating_point ) const;
	
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

    /************************/
    /* Non-Member functions */
    /************************/

    template<typename T>
    std::ostream& operator<<(std::ostream& os, Vec2d<T> const& pt)
    {
	os << "(" << pt.x << ", " << pt.y << ")";
	return os;
    }

    /*
     * Returns the cross product of the two vectors which is defined as
     * the Determinant of the two vectors. 
     * (The area of the surface that the two vectors
     * create when drawing a square with two of each of the vectors)
     */
    template<typename T>
    T cross(Vec2d<T> const& u, Vec2d<T> const& v);

    template<typename T>
    T dot(Vec2d<T> const& u, Vec2d<T> const& v);

    /**
     * Projects this line segment onto the given line (treats the
     * given line segment as a line)
     *
     * Template type FL can be used to specify precision, especially
     * useful if this Vec2d is of integer type
     *
     * a     : The line to project
     * b     : The line to project a on to
     * return: The projection onto the given line
     */
    template<typename T, typename FL = T>
    Vec2d<FL> project(Vec2d<T> const& v, Vec2d<T> const& s);

    /**
     * Scalar multiplication between an integer and a vec2d
     */
    template <typename T>
    Vec2d<T> operator*(T scalar, Vec2d<T> const& pt);

    template <typename T>
    Vec2d<T> operator*(Vec2d<T> const& pt, T scalar);
}

#include "vec2d.tcc"

#endif
