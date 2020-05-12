
#include <vector>

#include "../dalg/geometry/vec2d.h"

namespace dphys
{
    template <typename T>
    class Shape
    {
    public:
	Shape():
	    forces{}, angle{0}, vel{0,0},
	    acc{0,0}, pos{0,0}, mass{1}
	    {}
	
	Shape(dalg::Vec2d<T> const& pos, T mass):
	    forces{}, angle{0}, vel{0,0},
	    acc{0,0}, pos{pos}, mass{mass}
	    {}

	Shape(Shape const& other):
	    forces{other.forces},
	    angle{other.angle},
	    vel{other.vel},
	    acc{other.acc},
	    pos{other.pos},
	    mass{other.mass}
	    {}	    
	
	dalg::Vec2d<T> merge_forces()
	    {
		dalg::Vec2d<T> result{0,0};
		for (dalg::Vec2d<T>& vec : forces)
		{
		    result += vec;
		}	       		
		return result;
	    }

    protected:

	std::vector<dalg::Vec2d<T>> forces;
	
	T angle;
	dalg::Vec2d<T> vel;
	dalg::Vec2d<T> acc;

	T mass;
    };
}
