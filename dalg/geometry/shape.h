
#ifndef DALG_SHAPE
#define DALG_SHAPE

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
	
	const ShapeType type;
    };
}

#endif
