namespace phys
{
    template <typename T>
    inline std::optional<Collision<T>>
    collision(Shape<T>* a, Shape<T>* b)
    {
	if (a->type == ShapeType::circle &&
	    b->type == ShapeType::circle)
	{
	    return circle_circle_collision(*static_cast<Circle<T>*>(a),
					   *static_cast<Circle<T>*>(b));
	}
	return {};
    }

    template <typename T>
    inline std::optional<Collision<T>>
    circle_circle_collision(Circle<T> const& a, Circle<T> const& b)
    {
	T radius = a.get_radius() + b.get_radius();

	//Translation vector between midpoints
	dalg::Vec2d<T> ab{a.get_pos() - b.get_pos()};
	T distance = ab.length();

	//If they are to far away to collide, return monostate
	if (distance * distance > radius * radius)
	{
	    return {};
	}

	Collision<T> collision{
	        static_cast<Shape<T>*>(&a),
		static_cast<Shape<T>*>(&b)
		};
	
	Contact<T> c0{};

	//If they completely overlap
	if (distance == 0.0)
	{
	    c0.pos = a.get_pos();
	    c0.normal = dalg::Vec2d<T>{1,0};
	    c0.penetration = a.get_radius();

	    collision.push_back(c0);

	    return collision;
	}

	c0.penetration = radius - distance;

	//Normalize length of vector
	c0.normal = ab / distance;

	// Take b position and move it along the contact normal
	// the distance of b radius
	c0.pos = c0.normal * b.get_radius() + b.get_pos();

	collision.push_back(c0);

	return collision;
    }
}
