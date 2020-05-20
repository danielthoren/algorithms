
#ifndef VEC_2D
#define VEC_2D

#include <iostream>
#include <cmath>
#include <type_traits>
#include <variant>

namespace dalg
{
    const double DEFAULT_PREC = 0.0001;

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
	 * Takes care of comparisons of Floating fpoint template
	 * types. Uses prec vairable in comparison in the following way:
	 *
	 * abs( this.x - other.x ) < prec
	 */
	bool equals(Vec2d const& other, std::false_type is_floating_point ) const;
	
    public:	
	Vec2d(T x = 0, T y = 0, T prec = static_cast<T>( DEFAULT_PREC )) :
	    x{x}, y{y}, prec{prec}
	    {}
    
	Vec2d(Vec2d const& pt) :
	    x{pt.x}, y{pt.y}, prec{pt.prec}
	    {}

	~Vec2d() = default;

	Vec2d operator+(Vec2d const& other) const;
	Vec2d& operator+=(Vec2d const& other);

	Vec2d operator-(Vec2d const& other) const;
	Vec2d& operator-=(Vec2d const& other);


	Vec2d& operator*=(T scalar);

	Vec2d& operator=(Vec2d const& other);

	bool operator==(Vec2d const& other) const;	
	bool operator!=(Vec2d const& other) const;   

	/**
	 * Returns the length of this vector
	 */
	double length() const;

	/*
	 * Convenience method for calculating the distance between the
	 * tips of the vectors
	 */
	double distance(Vec2d const& other) const;

	T x;
	T y;
	T prec;

	constexpr static double PI = 3.141592653589793;
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
     * Returns the angle between the given vectors
     *
     * other : The vector to compare to
     *
     * return: The angle in degrees
     */
    template <typename T>
    double rad_angle(Vec2d<T> const& v1, Vec2d<T> const& v2);

    template <typename T>
    double angle(Vec2d<T> const& v1, Vec2d<T> const& v2);
    
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
    

    template <typename T>
    Vec2d<T> operator*(T scalar, Vec2d<T> const& pt);

    template <typename T>
    Vec2d<T> operator*(Vec2d<T> const& pt, T scalar);

    template <typename T>
    Vec2d<T> operator/(T scalar, Vec2d<T> const& pt);

    template <typename T>
    Vec2d<T> operator/(Vec2d<T> const& pt, T scalar);

    /**
     * Checks if the tree given points are collinear
     * (lie on the same line)
     *
     * a : Point a
     * b : Point b
     * c : Point c
     *
     * return: true if collinear otherwise false
     */
    template <typename T>
    bool collinear(dalg::Vec2d<T> const& a,
		   dalg::Vec2d<T> const& b,
		   dalg::Vec2d<T> const& c);

    /**
     * Checks if the given points are collinear
     * (lie on the same line)
     *
     * Time complexity: O(n)
     *
     * points: the given points
     *
     * return: true if collinear otherwise false
     */
    template <typename T>
    bool collinear(std::vector<dalg::Vec2d<T>> const& points);    
}

#include "vec2d.tcc"

#endif
