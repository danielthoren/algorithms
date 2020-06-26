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

    SECTION( "format constructor (min/max points swapped)" )
    {
	Vec2d<double> max{0,0};
	Vec2d<double> min{1,1};
	
	AABB<double> ab{min, max};

	REQUIRE( ab.get_min() == max );
	REQUIRE( ab.get_max() == min );	
    }    
}

TEST_CASE( "AABB == and != test", "[AABB]" )
{
    SECTION( "Normal true" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,0};
	Vec2d<double> max2{10,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1 == ab2 );
	CHECK_FALSE( ab1 != ab2 );
    }

    SECTION( "Normal false" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{11,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,0};
	Vec2d<double> max2{10,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1 != ab2 );
	CHECK_FALSE( ab1 == ab2 );
    }

    SECTION( "precision true" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10 + DEFAULT_PREC};
	
	AABB<double> ab1{min1, max1, 2 * DEFAULT_PREC};

	Vec2d<double> min2{0,0};
	Vec2d<double> max2{10,10};
	
	AABB<double> ab2{min2, max2, 2 * DEFAULT_PREC};

	CHECK( ab1 == ab2 );
	CHECK_FALSE( ab1 != ab2 );
    }

    SECTION( "precision false" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10 + DEFAULT_PREC};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,0};
	Vec2d<double> max2{10,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1 != ab2 );
	CHECK_FALSE( ab1 == ab2 );
    }
}

TEST_CASE( "AABB overlap test", "[AABB]" )
{
    SECTION( "overlap same y posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{5,0};
	Vec2d<double> max2{15,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap same y posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,5};
	Vec2d<double> max2{10,15};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{5,5};
	Vec2d<double> max2{15,15};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap top right corner posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10};
	Vec2d<double> max2{15,15};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap top left corner posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,10};
	Vec2d<double> max2{-10, 20};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap bottom left corner posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,0};
	Vec2d<double> max2{-10,-10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap bottom right corner posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,0};
	Vec2d<double> max2{15,-15};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap close top right corner negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10.01, 10.01};
	Vec2d<double> max2{15,15};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.overlap(ab2) );
    }

    SECTION( "overlap close top left corner negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{0,10.01};
	Vec2d<double> max2{-15,15};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.overlap(ab2) );
    }

    SECTION( "overlap close bottom left corner negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{-0.01, 0};
	Vec2d<double> max2{-15,-15};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.overlap(ab2) );
    }

    SECTION( "overlap close bottom right corner negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10.01, -0.01};
	Vec2d<double> max2{15,-15};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.overlap(ab2) );
    }

    SECTION( "overlap 0-height posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10};
	Vec2d<double> max2{11,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap 0-width posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10};
	Vec2d<double> max2{10,11};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap point posetive" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10};
	Vec2d<double> max2{10,10};
	
	AABB<double> ab2{min2, max2};

	CHECK( ab1.overlap(ab2) );
    }

    SECTION( "overlap 0-height negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10.001, 10};
	Vec2d<double> max2{11,10};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.overlap(ab2) );
    }

    SECTION( "overlap 0-width negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10,10.001};
	Vec2d<double> max2{10,11};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.overlap(ab2) );
    }

    SECTION( "overlap point negative" )
    {
	Vec2d<double> min1{0,0};
	Vec2d<double> max1{10,10};
	
	AABB<double> ab1{min1, max1};

	Vec2d<double> min2{10.001, 10.001};
	Vec2d<double> max2{10.001, 10.001};
	
	AABB<double> ab2{min2, max2};

	CHECK_FALSE( ab1.overlap(ab2) );
    }    
}
