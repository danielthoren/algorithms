
#ifndef DALG_SHAPE
#define DALG_SHAPE

#include <vector>
#include <optional>


#include "vec2d.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace dalg
{    
    template<typename T>
    class Circle;

    /**
     * Author: Daniel Thorén
     *
     * Contains information about a contact point in a collision
     * between two shapes
     */
    template <typename T>
    struct Contact
    {
	bool operator==(Contact<T> const& other) const
	    {
		if (pos != other.pos)
		{
		    if (DEBUG)
		    {
			std::cout <<
			    "Contact::operator== " <<
			    "pos(" << pos.x << ", " << pos.y <<
			    ") != other.pos(" <<
			    other.pos.x << ", " << other.pos.y << ")" <<
			    std::endl;
		    }
		    return false;
		}
		if (normal != other.normal)
		{
		    if (DEBUG)
		    {
			std::cout <<
			    "Contact::operator== " <<
			    "normal(" << normal.x << ", " << normal.y <<
			    ") != other.normal(" <<
			    other.normal.x << ", " << other.normal.y << ")" <<
			    std::endl;
		    }
		    return false;
		}		
		if (penetration != other.penetration)
		{
		    if (DEBUG)
		    {
			std::cout <<
			    "Contact::operator== " <<
			    "penetration(" << penetration <<
			    ") != other.penetration(" <<
			    other.penetration << ")" << std::endl;
		    }
		    return false;
		}

		return true;
	    }

	bool operator!=(Contact<T> const& other) const
	    {
		return !(*this == other);
	    }
	
	Vec2d<T> pos;    //The position of the contact point
	Vec2d<T> normal; //The normal of the contact point
	T penetration;   //The penetration depth along this contact point normal
    };

    template <typename T>
    class Shape;

    /**
     * Author: Daniel Thorén
     *
     * Contains information about a collision between two shapes
     */
    template <typename T>
    struct Collision
    {
	Collision() :
	    contacts{},
	    contact_count{0},
	    A{nullptr},
	    B{nullptr}
	    {}

	bool operator==(Collision<T> const& other) const
	    {
		if (contacts.size() != other.contacts.size())
		{
		    if (DEBUG)
		    {
			std::cout <<
			    "Collision::operator== " <<
			    "contacts.size() != other.contacts.size()" <<
			    std::endl;
		    }
		    return false;
		}
		
		for (unsigned c{0}; c < contacts.size(); c++)
		{
		    if (contacts[c] != other.contacts[c])
		    {
			if (DEBUG)
			{
			    std::cout <<
				"Collision::operator== " <<
				"contacts[" << c <<
				"] != other.contacts[" << c <<"]" <<
				std::endl;			    
			}
			return false;
		    }
		}

		return contact_count == other.contact_count &&
		    (*A) == (*other.A) &&
		    (*B) == (*other.B);
	    }
	
	std::vector<Contact<T>> contacts;
	unsigned contact_count;
	Shape<T>* A;
	Shape<T>* B;
    };

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
	Shape(Vec2d<T> const& pos, ShapeType type): pos{pos}, type{type}
	    {}

	bool operator==(Shape<T> const& other) const
	    {
		return pos == other.pos && type == other.type;
	    }

	bool operator!=(Shape<T> const& other) const
	    {
		return !(*this == other);
	    }

	Vec2d<T> get_pos() const
	    {
		return pos;
	    }

	Vec2d<T> pos;
	const ShapeType type;
    };

#include "circle.h"
}

#endif
