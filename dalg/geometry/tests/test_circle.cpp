#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#include "../vec2d.h"
#include "../circle.h"
#include "../utility.h"
#include "../aabb.h"

#define DEBUG 1

using namespace dalg;

TEST_CASE( "Circle constructor test", "[Circle]" )
{
    SECTION( "Normal constructor" )
    {
	Vec2d<double> center{0,0};
	
	Circle<double> c(center, 5);

	REQUIRE( c.center == Vec2d<double>{0,0} );
	REQUIRE( c.radius == 5 );
    }

    SECTION( "Default constructor" )
    {	
	Circle<double> c;

	REQUIRE( c.center == Vec2d<double>{0,0} );
	REQUIRE( c.radius == 0 );
    }    
}

TEST_CASE( "Circle == and != test", "[Circle]" )
{
    SECTION( "Normal true" )
    {
	Vec2d<double> center{0,0};
	
	Circle<double> c1(center, 5);
	Circle<double> c2(center, 5);

	CHECK( c1 == c2 );
	CHECK_FALSE( c1 != c2 );
    }

    SECTION( "Normal false" )
    {
	Vec2d<double> center{0,0};
	
	Circle<double> c1(center, 5);

	Vec2d<double> center2{1,0};
	Circle<double> c2(center2, 5);

	CHECK_FALSE( c1 == c2 );
	CHECK( c1 != c2 );
    }
    
    SECTION( "center precision false" )
    {
    	Vec2d<double> center{0,0};
	
    	Circle<double> c1(center, 5);

    	Vec2d<double> center2{0,0 + DEFAULT_PREC};
    	Circle<double> c2(center2, 5);

    	CHECK_FALSE( c1 == c2 );
    	CHECK( c1 != c2 );
    }

    SECTION( "center precision true" )
    {
	Vec2d<double> center{0,0};
	
	Circle<double> c1(center, 5, 2*DEFAULT_PREC);

	Vec2d<double> center2{0,0 + DEFAULT_PREC};
	Circle<double> c2(center2, 5, 2*DEFAULT_PREC);

	CHECK( c1 == c2 );
	CHECK_FALSE( c1 != c2 );
    }

    SECTION( "radius precision false" )
    {
	Vec2d<double> center{0,0};
	
	Circle<double> c1(center, 5, DEFAULT_PREC);

	Circle<double> c2(center, 5 + DEFAULT_PREC, DEFAULT_PREC);

	CHECK( c1 == c2 );
	CHECK_FALSE( c1 != c2 );
    }

    SECTION( "radius precision true" )
    {
	Vec2d<double> center{0,0};
	
	Circle<double> c1(center, 5, 2*DEFAULT_PREC);

	Circle<double> c2(center, 5 + DEFAULT_PREC, 2*DEFAULT_PREC);

	CHECK( c1 == c2 );
	CHECK_FALSE( c1 != c2 );
    }
    
}


TEST_CASE( "Circle get_aabb() test", "[Circle]" )
{
    SECTION( "Normal (0,0)" )
    {
	Vec2d<double> center{0,0};	
	Circle<double> c1(center, 5);

	Vec2d<double> v1{0 - 5, 0 - 5};
	Vec2d<double> v2{0 + 5, 0 + 5};

	CHECK( c1.get_aabb() == AABB<double>{v1, v2} );
    }

    SECTION( "Normal (10,10)" )
    {
	Vec2d<double> center{10,10};	
	Circle<double> c1(center, 5);

	Vec2d<double> v1{10 - 5, 10 - 5};
	Vec2d<double> v2{10 + 5, 10 + 5};

	CHECK( c1.get_aabb() == AABB<double>{v1, v2} );
    }

    SECTION( "radius = 0" )
    {
	Vec2d<double> center{10,10};	
	Circle<double> c1(center, 0);

	Vec2d<double> v1{10 - 0, 10 - 0};
	Vec2d<double> v2{10 + 0, 10 + 0};

	CHECK( c1.get_aabb() == AABB<double>{v1, v2} );
    }    
}
