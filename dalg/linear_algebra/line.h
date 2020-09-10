#ifndef DALG_LINE
#define DALG_LINE

#include "vec2d.h"
#include "utility.h"

namespace dalg
{
    /**
     * Author: Daniel Thorén
     *
     * Class representing a 2d line. Each endpoint of the line is
     * represented by a 2d point. The class supports various operations.
     */
    template <typename T>
    class Line
    {
    public:
	Line(Vec2d<T> p0, Vec2d<T> u,
	     p_type prec = static_cast<p_type>( DEFAULT_PREC ))
	    : p0{p0}, u{u}, prec{prec}
	    {}
    
	Line(T x0, T y0, T x1, T y1,
	     p_type prec = static_cast<p_type>( DEFAULT_PREC ))
	    : Line({x0, y0}, {x1, y1 }, prec)
	    {}

	bool operator==(Line<T> const& other) const;
	bool operator!=(Line<T> const& other) const;

	//p(s) = p0 + su
	Vec2d<T> p0;
	Vec2d<T> u;
	p_type prec;
    };


    /**
     * Author: Daniel Thorén
     *
     * Checks if the given lines are parallel
     *
     * l1    : First line
     * l2    : Second line
     *
     * return: True if l1 & l2 are parallel, else false 
     */
    template <typename T>
    bool parallel(Line<T> const& l1, Line<T> const& l2);


    
    /**
     * Author: Daniel Thorén
     *
     * Calculates the projection of point pt on the line l
     *
     * pt    : The point to project
     * l     : The line to project onto
     *
     * return: The projection of pt onto l
     */
    template <typename T>
    Vec2d<T> project(Vec2d<T> const& pt, Line<T> const& l);
}

#include "line.tcc"

#endif
