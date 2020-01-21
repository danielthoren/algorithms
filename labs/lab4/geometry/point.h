
#ifndef POINT_2D
#define POINT_2D

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
    
    /*
     * Scalar product
     */
    T operator*(point const& other) const;
    point operator*(T scalar) const;

    point& operator=(point const& other);

    bool operator==(point const& other) const;
    bool operator!=(point const& other) const;
    bool operator<(point const& other) const;
    bool operator<=(point const& other) const;
    bool operator>(point const& other) const;
    bool operator>=(point const& other) const;

    /*
     * Determinant (The area of the surface that the two vectors
     * create when drawing a square with two of each of the vectors)
     */
    T determinant(point const& other) const;

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

/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/


/**********************/
/* Member functions   */
/**********************/

#include <cmath>

template <typename T>
point<T> point<T>::operator+(point<T> const& other) const
{
    point<T> tmp{*this};
    tmp += other;
    return tmp;
}

template <typename T>
point<T>& point<T>::operator+=(point<T> const& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
point<T> point<T>::operator-(point<T> const& other) const
{
    point<T> tmp{*this};
    tmp -= other;
    return tmp;
}

template <typename T>
point<T>& point<T>::operator-=(point<T> const& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template <typename T>
T point<T>::operator*(point<T> const& other) const
{
    return x * other.x + y * other.y;
}

template <typename T>
point<T>& point<T>::operator=(point const& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

template <typename T>
bool point<T>::operator==(point<T> const& other) const
{
    return std::abs( std::abs(x) - std::abs(other.x) ) <= prec &&
	std::abs( std::abs(y) - std::abs(other.y) ) <= prec;
}

template <typename T>
bool point<T>::operator!=(point<T> const& other) const
{
    return !( *this == other );
}

template <typename T>
bool point<T>::operator<(point<T> const& other) const
{
    return this->length() < other.length();
}

template <typename T>
bool point<T>::operator<=(point<T> const& other) const
{
    return *this < other || *this == other;
}

template <typename T>
bool point<T>::operator>(point<T> const& other) const
{
    return !(*this <= other);
}

template <typename T>
bool point<T>::operator>=(point<T> const& other) const
{
    return *this > other || *this == other;
}

template <typename T>
T point<T>::distance(point<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return std::sqrt(x_dist^2 + y_dist^2);
}

template <typename T>
point<T> point<T>::distance_vec(point<T> const& other) const
{
    T x_dist = std::abs(x - other.x);
    T y_dist = std::abs(y - other.y);

    return point<T>{x_dist, y_dist};
}

template <typename T>
T point<T>::determinant(point<T> const& other) const
{
    return x * other.y - y * other.x;
}

template <typename T>
double point<T>::length() const
{
    return std::sqrt( std::pow(x, 2) + std::pow(y, 2) );
}


/************************/
/* Non-Member functions */
/************************/

template <typename T>
point<T> operator*(T scalar, point<T> const& pt)
{
    return point<T>{pt.x * scalar, pt.y * scalar};
}

template <typename T>
point<T> operator*(point<T> const& pt, T scalar)
{
    return point<T>{pt.x * scalar, pt.y * scalar};
}

#endif
