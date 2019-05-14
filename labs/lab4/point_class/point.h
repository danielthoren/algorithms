
#ifndef POINT_2D
#define POINT_2D

template <typename T>
class Point_2d
{
    Point_2d(T x_cord = 0, T y_cord = 0) :
	x_cord{x_cord}, y_cord{y_cord}
	{}
    
    Point_2d(Point_2d const& pt) :
	x_cord{pt.x_cord}, y_cord{pt.y_cord}
	{}

    ~Point_2d() = default;

    Point_2d operator+(Point_2d const& other) const;
    Point_2d& operator+=(Point_2d const& other);

    Point_2d operator-(Point_2d const& other) const;
    Point_2d& operator-=(Point_2d const& other);

    /*
     * Cross product
     */
    Point_2d operator*(Point_2d const& other) const;
    Point_2d& operator*=(Point_2d const& other);

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
    T distance(Point_2d const& other) const;
    double angle(Point_2d const&other) const;

    T length();
    
private:
    
    T x_cord;
    T y_cord;
};

#include "point.tcc"

#endif
