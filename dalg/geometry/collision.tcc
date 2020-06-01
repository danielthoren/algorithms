

template <typename T>
inline std::optional<dalg::Collision<T>>
dalg::collision(dalg::Shape<T>* a, dalg::Shape<T>* b)
{
    if (a->type == dalg::ShapeType::circle &&
	b->type == dalg::ShapeType::circle)
    {
	return circle_circle_collision(*static_cast<dalg::Circle<T>*>(a),
				       *static_cast<dalg::Circle<T>*>(b));
    }
    return {};
}

template <typename T>
inline std::optional<dalg::Collision<T>>
dalg::circle_circle_collision(dalg::Circle<T>& a, dalg::Circle<T>& b)
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
    collision.A = static_cast<Shape<T>*>(&a);
    collision.B = static_cast<Shape<T>*>(&b);
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
