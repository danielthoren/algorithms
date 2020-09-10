#ifndef DALG_CIRCLE
#define DALG_CIRCLE

#include <optional>

#include "vec2d.h"
#include "aabb.h"
#include "utility.h"

namespace dalg
{
    template <typename T>
    class Circle
    {
    public:
	Circle() :
	    center{}, radius{0}, prec{DEFAULT_PREC}
	    {}
	
	Circle(Vec2d<T> const& center, T radius, p_type prec = static_cast<p_type>(DEFAULT_PREC)) :
	    center{center}, radius{radius}, prec{prec}
	    {
		this->center.prec = prec;
	    }

	bool operator==(Circle<T> const& other) const;

	bool operator!=(Circle<T> const& other) const;

	/**
	 * Returns the AABB that encloses this circle segment
	 *
	 * return: AABB encloding this circle
	 */
	AABB<T> get_aabb() const;

	Vec2d<T> center;
	T radius;
	p_type prec;
    };
}

#include "circle.tcc"

#endif
