#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

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

	auto col = intersect<double>(c1, c2);

	REQUIRE( std::holds_alternative<Vec2d<double>>(col) );
	    
	Vec2d<double> res = std::get<Vec2d<double>>(col);
	
	CHECK( res == Vec2d<double>{0,5} );
    }
}
