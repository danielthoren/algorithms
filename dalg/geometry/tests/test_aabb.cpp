#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#include "../vec2d.h"
#include "../aabb.h"

#define DEBUG 1

using namespace dalg;

TEST_CASE( "AABB constructor test", "[AABB]" )
{
    SECTION( "Normal constructor" )
    {
	Vec2d<double> min{0,0};
	Vec2d<double> max{1,1};
	
	AABB<double> ab{min, max};

	REQUIRE( ab.get_min() == min );
	REQUIRE( ab.get_max() == max );	
    }
}

TEST_CASE( "AABB collision test" )
{
    SECTION( "collision same y posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{5,0};
	Vec2d<double> max2{15,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision same y posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,5};
	Vec2d<double> max2{10,15};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{5,5};
	Vec2d<double> max2{15,15};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision top right corner posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10};
	Vec2d<double> max2{15,15};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision top left corner posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,10};
	Vec2d<double> max2{-10, 20};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision bottom left corner posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,0};
	Vec2d<double> max2{-10,-10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision bottom right corner posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,0};
	Vec2d<double> max2{15,-15};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision close top right corner negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10.01, 10.01};
	Vec2d<double> max2{15,15};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.collision(ab2) );
    }

    SECTION( "collision close top left corner negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,10.01};
	Vec2d<double> max2{-15,15};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.collision(ab2) );
    }

    SECTION( "collision close bottom left corner negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{-0.01, 0};
	Vec2d<double> max2{-15,-15};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.collision(ab2) );
    }

    SECTION( "collision close bottom right corner negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10.01, -0.01};
	Vec2d<double> max2{15,-15};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.collision(ab2) );
    }

    SECTION( "collision 0-height posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10};
	Vec2d<double> max2{11,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision 0-width posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10};
	Vec2d<double> max2{10,11};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision point posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10};
	Vec2d<double> max2{10,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.collision(ab2) );
    }

    SECTION( "collision 0-height negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10.001, 10};
	Vec2d<double> max2{11,10};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.collision(ab2) );
    }

    SECTION( "collision 0-width negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10.001};
	Vec2d<double> max2{10,11};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.collision(ab2) );
    }

    SECTION( "collision point negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10.001, 10.001};
	Vec2d<double> max2{10.001, 10.001};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.collision(ab2) );
    }    
}
