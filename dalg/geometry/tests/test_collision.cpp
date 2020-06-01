#include "catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>
#include <optional>

#include "../shape.h"
#include "../circle.h"
#include "../collision.h"

#define DEBUG 1

using namespace dalg;

TEST_CASE( "Circle-circle collision test", "[Collision]" )
{
    
    //--------------------Test random ---------------------------
    SECTION( "Test edge collision" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Circle<double> c2{Vec2d<double>{0,10}, 5};

	Shape<double>* s1 = &c1;
	Shape<double>* s2 = &c2;

	auto col = collision(s1, s2);

	REQUIRE( col );
	    
	Collision<double> col_act = col.value();

	Contact<double> c0{Vec2d<double>{0,5},
			   Vec2d<double>{0,-1},
			   0};

	Collision<double> col_c;
	    
	col_c.contacts.push_back(c0);
	col_c.contact_count = 1;
	col_c.A = s1;
	col_c.B = s2;

	bool res = col_act == col_c;

	CHECK( res );
    }
}
