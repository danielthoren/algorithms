
#include "../dalg/geometry/circle.h"

#include "shape.h"

namespace dphys
{
    template <typename T>
    class Circle : public Shape
    {
    public:
	
	Circle(dalg::Vec2d<T> const& pos, T radius) :
	    Shape(),
	    circle(pos, radius)
	    {}

	Circle(Circle<T> const& other) :
	    Shape(other),
	    circle{other.circle}
	    {}

	void check_collision(Circle const& other)
	    {
		if (circle.collision(other.circle))
		{
		    dalg::Vec2d<T> mid_mid{ dalg::project(circle.center_point, other.center_point) };
		    dalg::Vec2d<T> f_n{ dalg::project(vel, mid_mid) };
		    f_n *= -1;

		    forces.add(f_n);
		    forces.add(f_n);		    
		}
	    }

	void update(double time_step)
	    {
		dalg::Vec2d<T> force{ merge_forces() };
		acc += force / mass;
		vel += acc * time_step;
		
		circle.center_point += vel * time_step + 0.5 * acc * std::pow(time_step, 2);
	    }

    private:
	dalg::Circle circle;
	
    };
}
