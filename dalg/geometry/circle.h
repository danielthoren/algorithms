#ifndef DALG_CIRCLE
#define DALG_CIRCLE

#include <optional>

#include "vec2d.h"
#include "shape.h"
#include "aabb.h"
#include "utility.h"

namespace dalg
{
    template <typename T>
    class Circle : public Shape<T>
    {
    public:
	Circle() :
	    Shape<T>(ShapeType::circle), center{}, radius{0}, prec{DEFAULT_PREC}
	    {}
	
	Circle(Vec2d<T> const& center, T radius, p_type prec = static_cast<p_type>(DEFAULT_PREC)) :
	    Shape<T>(ShapeType::circle), center{center}, radius{radius}, prec{prec}
	    {
		this->center.prec = prec;
	    }

	bool operator==(Circle<T> const& other) const
	    {
		p_type precision = get_pref_prec(prec, other.prec);
		
		return std::abs(radius - other.radius) < precision && this->center == other.center;
	    }

	bool operator!=(Circle<T> const& other) const
	    {
		return !(*this == other);
	    }

	/**
	 * Returns the AABB that encloses this circle segment
	 *
	 * return: AABB encloding this circle
	 */
	AABB<T> get_aabb() const
	    {
		Vec2d<T> max{center.x + radius, center.y + radius}; //up right corner
		Vec2d<T> min{center.x - radius, center.y - radius}; //down left corner

		return AABB{min, max};
	    }

	Vec2d<T> center;
	T radius;
	p_type prec;
    };
}

#include "circle.tcc"

#endif
