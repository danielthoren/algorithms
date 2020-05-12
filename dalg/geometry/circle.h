#ifndef DALG_CIRCLE
#define DALG_CIRCLE

#include <optional>

#include "vec2d.h"
#include "shape.h"

namespace dalg
{
    template <typename T>
    class Circle : public Shape<T>
    {
    public:
	Circle(Vec2d<T> const& pos, T radius) :
	    Shape<T>(pos), radius{radius}
	    {}

	std::optional<Collision<T>>
	collision(Shape<T>& other) override
	    {
		return other.circle_collision(*this);
	    }

	std::optional<Collision<T>>
	circle_collision(Circle<T>& other) override
	    {
		return circle_circle_collision(*this, other);
	    }

	bool operator==(Circle<T>& other) const
	    {
		std::cout << "in circle operator" << std::endl;
		return radius == other.radius && this->pos == other.pos;
	    }

	bool operator!=(Circle<T>& other) const
	    {
		return !(*this == other);
	    }

	T get_radius() const
	    {
		return radius;
	    }

    private:
	T radius;
    };

    template <typename T>
    std::optional<Collision<T>>
    circle_circle_collision(Circle<T>& b, Circle<T>& a)
    {
	T radius = a.get_radius() + b.get_radius();

	//Translation vector between midpoints
	Vec2d<T> ab{a.get_pos() - b.get_pos()};
	T distance = ab.length();
	
	//If they are to far away to collide, return monostate
	if (distance * distance > radius * radius)
	{
	    return {};
	}

	Collision<T> collision{};
	collision.A = dynamic_cast<Shape<T>*>(&a);
	collision.B = dynamic_cast<Shape<T>*>(&b);
	collision.contact_count = 1;

	collision.contacts.emplace_back();
	Contact<T>* c0 = &collision.contacts[0];

	//If they completely overlap
	if (distance == 0.0)
	{
	    c0->pos = a.get_pos();
	    c0->normal = Vec2d<T>{1,0};
	    c0->penetration = a.get_radius();

	    return collision;
	}

	c0->penetration = radius - distance;

	//Normalize length of vector
	c0->normal = ab / distance;

	// Take b position and move it along the contact normal
	// the distance of b radius
	c0->pos = c0->normal * b.get_radius() + b.get_pos();

	return collision;
    }

}

#endif
