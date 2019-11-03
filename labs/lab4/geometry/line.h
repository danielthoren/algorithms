#ifndef LINE_
#define LINE_

#include "point.h"

template <typename T>
class line
{
public:
    line(point<T> p0, point<T> p1);
    
    line(T x0, T y0, T x1, T y1);

    bool operator==(line<T> const& other) const;
    bool operator!=(line<T> const& other) const;

    bool is_parallel(line<T> const& other) const;

    bool on_line(point<T> const& pt) const;

    point<T> orthogonal_projection(point<T> const& pt) const;

    /*
     * Returns the point where this line and other intersects
     *
     * Given lines 
     * L1(t) = p + t * U
     * L2(s) = q + s * V
     * 
     * We get the constant t on line L1 where the intersection occurs as:
     * t = (q - p) x V / U x V
     *
     * Then we obtain the actual intersection point from the following:
     * p_inter = p + t * U
     */
    point<T> intersection(line<T> const& other) const;   
    
    //p(s) = p0 + su
    point<T> p0;
    point<T> u;    // u = p1 - p0
};

/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/
template <typename T>
line<T>::line(point<T> p0, point<T> p1) : p0{p0}, u{p1 - p0}
{}


template <typename T>
line<T>::line(T x0, T y0, T x1, T y1) : p0{x0, y0}, u{ point<T>{x1, y1} - p0 }
{}


template <typename T>
bool line<T>::is_parallel(line<T> const& other) const
{
    return u.determinant(other.u) == 0;
}


template <typename T>
bool line<T>::operator==(line<T> const& other) const
{
    return is_parallel(other) && u.determinant(p0 - other.p0) == 0;
}

template <typename T>
bool line<T>::operator!=(line<T> const& other) const
{
    return ! (*this == other);
}

template <typename T>
bool line<T>::on_line(point<T> const& pt) const
{
	    
}


template <typename T>
point<T> line<T>::orthogonal_projection(point<T> const& pt) const
{
    return ((pt * u) / (u * u)) * u;
}

/*
 * Returns the point where this line and other intersects
 *
 * Given lines 
 * L1(t) = p + t * U
 * L2(s) = q + s * V
 * 
 * We get the constant t on line L1 where the intersection occurs as:
 * t = (q - p) x V / U x V
 *
 * Then we obtain the actual intersection point from the following:
 * p_inter = p + t * U
 */
template <typename T>
point<T> line<T>::intersection(line<T> const& other) const
{
    T t = other.u.determinant( (other.p0 - p0) ) / other.u.determinant(u);
    point<T> inter{ p0 + (t * u) };
    return inter;
}   

#endif
