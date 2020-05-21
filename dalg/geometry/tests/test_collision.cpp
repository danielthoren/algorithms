#include "catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#define DEBUG 1

#include "../vec2d.h"
#include "../circle.h"

using namespace dalg;

TEST_CASE( "Circle-circle collision test", "[Collision]" )
{
    
    //--------------------Test random ---------------------------
    SECTION( "Test normal collision" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Circle<double> c2{Vec2d<double>{5,0}, 5};

        auto col = c1.collision(c2);

	REQUIRE( col );
	    
	Collision<double>& col_act = col.value();

	Contact<double> c0{Vec2d<double>{0,0},
			   Vec2d<double>{-1,0},
			   5};

	Collision<double> col_c;
	    
	col_c.contacts.push_back(c0);
	col_c.contact_count = 1;
	col_c.A = &c1;
	col_c.B = &c2;

	CHECK( col_act == col_c );
    }
}
