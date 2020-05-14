
#ifndef VEC_2D
#define VEC_2D

#include <iostream>
#include <cmath>
#include <type_traits>
#include <variant>

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
	 * Takes care of comparisons of Floating fpoint template
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

    /*
     * Returns true if the given line segment contains the given line segment
     * contains the point.
     *
     * The line segment is defined as follows:
     *
     * L = p + u * x : x = 1
     *
     * p     : line segment point
     * u     : line segment vector
     * point : The point to check
     *
     * return: True if the line segment contains the point
     */
    template <typename T>
      bool on_line(Vec2d<T> const& line_p,
			 Vec2d<T> const& line_u,
			 Vec2d<T> const& point);

    /**
     * Returns the point where this lines intersects If they
     * don't intersect
     *
     * The line segments is defined as follows:
     *
     * L1(x) = p + u * x : x = 1
     * L2(x) = q + v * x : x = 1
     *
     * other : The line to check for intersection with
     * return: The intersection point. If there is non then return point with
     *         std::numeric_limits<T>::min() as its values
     */
    template <typename T>
    std::variant<std::monostate, Vec2d<T>, std::pair<Vec2d<T>, Vec2d<T>>>
      line_seg_intersection(Vec2d<T> const& p,
			    Vec2d<T> const& u,
			    Vec2d<T> const& q,
			    Vec2d<T> const& v);
}

#include "vec2d.tcc"

#endif
