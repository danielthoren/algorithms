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

	/**
	 * Checks if the Lines are equal (parallel and has the same points)
	 */
	bool operator==(Line<T> const& other) const;
	bool operator!=(Line<T> const& other) const;

	bool is_parallel(Line<T> const& other) const;

	/**
	 * Returns p0
	 */
	Vec2d<T> get_start() const;

	/**
	 * Returns u
	 */
	Vec2d<T> get_vec() const;

    private:
	//p(s) = p0 + su
	Vec2d<T> p0;
	Vec2d<T> u;
	p_type prec;
    };

    template <typename T>
    Vec2d<T> project(Vec2d<T> const& pt, Line<T> const& l);
}

#include "line.tcc"

#endif
