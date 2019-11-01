#include <iostream>

#include "point.h"

using namespace std;

template <typename T>
class line_segment
{
public:
    line_segment(point<T> p0, point<T> p1) : p0{p0}, u{p1 - p0}
	{}

    line_segment(T x0, T y0, T x1, T y1) : p0{x0, y0}, u{ point<T>{x1, y1} - p0 }
	{}

    bool is_parallel(line_segment<T> const& other) const
	{
	    return u.determinant(other.u) = 0;
	}

    bool is_same(line_segment<T> const& other) const
	{
	    return is_parallel(other) && u.determinant(p0 - other.po) == 0;
	}

    bool on_line(point<T> const& pt) const
	{
	}

    /*
     * Returns the point where this line_segment and other intersects
     *
     * Given line_segments 
     * L1(t) = p + t * U
     * L2(s) = q + s * V
     * 
     * We get the constant t on line_segment L1 where the intersection occurs as:
     * t = (q - p) x V / U x V
     *
     * Then we obtain the actual intersection point from the following:
     * p_inter = p + t * U
     */
    point<T> intersection(line_segment<T> const& other) const
	{
	    T t = other.u.determinant( (other.p0 - p0) ) / u.determinant(other.u);
	    point<T> inter = p0 + t * u;	    
	}   
    
private:
    
    //p(s) = p0 + su
    point<T> p0;
    point<T> u;    // u = p1 - p0
};

line_segment<int> read_line_segment()
{
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    line_segment<int> l1{x1, y1, x2, y2};

    return l1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int cases{};
    cin >> cases;

    for (int i{0}; i < cases; i++)
    {	
	line_segment<int> l1 = read_line_segment();
	line_segment<int> l2 = read_line_segment();

	
    }
    
}
