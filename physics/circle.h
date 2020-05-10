
#include "../dalg/geometry/circle.h"

#include "shape.h"

namespace dphys
{
    template <typename T>
    class Circle : public Shape
    {
    public:
	Circle() :
	    Shape()
	    {}
	
	Circle(dalg::Vec2d<T> const& pos) :
	    Shape(pos)
	    {}

	Circle(Circle<T> const& other) :
	    Shape(other)
	    {}	
	
    };
}
