
#ifndef DALG_SHAPE
#define DALG_SHAPE

#include "aabb.h"

namespace dalg
{    
    enum ShapeType
    {
	shape,
	circle,
	lineSegment,
	square,
	polygon
    };

    /**
     * Author: Daniel Thorén
     *
     * Class containing common features for all dalg shapes
     */
    template <typename T>
    class Shape
    {
    public:
	Shape(ShapeType type) : type{type}
	    {}

	virtual AABB<T> get_aabb() const = 0;

	inline ShapeType get_type() const
	    {
		return type;
	    }

    private:	
	ShapeType type;
    };
}

#endif
