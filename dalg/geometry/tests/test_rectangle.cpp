#include "catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "../rectangle.h"
#include "../vec2d.h"
#include "../line_segment.h"

#define DEBUG 1

using namespace dalg;


TEST_CASE( "Rectangle Constructor test", "[Rectangle]")
{
    SECTION( "Test Vec2d constructor" )
    {
	std::cout << "in rectangle test" << std::endl;
	
	Vec2d<int> c1(0,0);
	Vec2d<int> c2(0,1);
	Vec2d<int> c3(1,1);
	Vec2d<int> c4(0,1);

	Rectangle<int> r1(c1, c2, c3, c4);

	std::vector<Vec2d<int>>& c = r1.get_corners();
        REQUIRE( c[0] == c1 );
	REQUIRE( c[1] == c2 );
	REQUIRE( c[2] == c3 );
	REQUIRE( c[3] == c4 );
    }

    SECTION( "Vec2d constructor with wrong angle args" )
    {
	Vec2d<int> c1(0,0);
	Vec2d<int> c2(1,1);
	Vec2d<int> c3(0,1);
	Vec2d<int> c4(-1,-1);

	CHECK_THROWS_AS( Rectangle<int>(c1, c2, c3, c4), dalg::BadArgumentException );
    }

    SECTION( "Vec2d constructor with wrong order args" )
    {
	Vec2d<int> c1(0,0);
	Vec2d<int> c2(0,1);
	Vec2d<int> c3(1,1);
	Vec2d<int> c4(1,0);

	CHECK_THROWS_AS( Rectangle<int>(c1, c3, c2, c4) ,dalg::BadArgumentException);
    }

    SECTION( "copy constructor" )
    {
	Vec2d<int> c1(0,0);
	Vec2d<int> c2(0,1);
	Vec2d<int> c3(1,1);
	Vec2d<int> c4(0,1);

	Rectangle<int> r(c1, c2, c3, c4);	

	Rectangle<int> r1(r);	

	std::vector<Vec2d<int>>& c = r1.get_corners();
	REQUIRE( c[0] == c1 );
	REQUIRE( c[1] == c2 );
	REQUIRE( c[2] == c3 );
	REQUIRE( c[3] == c4 );
    }
}


TEST_CASE( "Rectangle min_max test", "[Rectangle]")
{
    SECTION( "min_max test 1" )
    {
	Vec2d<int> c1(0,1);
	Vec2d<int> c2(1,0);
	Vec2d<int> c3(1,2);
	Vec2d<int> c4(2,1);

	Rectangle<int> r1(c1, c2, c3, c4);

	std::pair<Vec2d<double>, Vec2d<double>> ret = r1.get_min_max_projection<double>( Vec2d<int>(1,0) );
	ret.first.prec = 0.1;
	ret.second.prec = 0.1;

        CHECK( ret.first == Vec2d<double>(0,0) );
	CHECK( ret.second == Vec2d<double>(2,0) );
    }
}

TEST_CASE( "Rectangle center point test", "[Rectangle]")
{
    SECTION( "Axel Aligned" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> ret = r1.get_center_point();
	ret.prec = 0.01;

        CHECK( ret == Vec2d<double>(0.5, 0.5) );
    }

    SECTION( "rotated 45" )
    {
	Vec2d<double> c1(0,1);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(0,-1);
	Vec2d<double> c4(-1,0);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> ret = r1.get_center_point();
	ret.prec = 0.01;

        CHECK( ret == Vec2d<double>(0, 0) );
    }
}

TEST_CASE( "Rectangle collision x-axis test", "[Rectangle]")
{
    SECTION( "same angle overlap x-axis" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0.5,1);
	Vec2d<double> a2(2  ,1);
	Vec2d<double> a3(2  ,0);
	Vec2d<double> a4(0.5,0);

	Rectangle<double> r2(a1, a2, a3, a4);
       
        CHECK( r1.collision(r2) );
    }

    SECTION( "same angle x-axis, only collision in line segment" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1,1);
	Vec2d<double> a2(2,1);
	Vec2d<double> a3(2,0);
	Vec2d<double> a4(1,0);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "same angle x-axis, no collision" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(10,0);
	Vec2d<double> a2(11,0);
	Vec2d<double> a3(11,1);
	Vec2d<double> a4(10,1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( !r1.collision(r2) );
    }    

    SECTION( "different angle x-axis, deep collision" )
    {
	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0.75,2);
	Vec2d<double> a2(2   ,2);
	Vec2d<double> a3(2   ,0);
	Vec2d<double> a4(0.75,0);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "different angle x-axis, only collision in point" )
    {
	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1,1);
	Vec2d<double> a2(2,1);
	Vec2d<double> a3(2,0);
	Vec2d<double> a4(1,0);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "different angle x-axis, no collision far" )
    {
	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(10,10);
	Vec2d<double> a2(11,10);
	Vec2d<double> a3(11,11);
	Vec2d<double> a4(10,11);

	Rectangle<double> r2(a1, a2, a3, a4);

	CHECK( !r1.collision(r2) );
    }

    SECTION( "different angle x-axis, no collision close" )
    {
	Vec2d<double> c1(0.5,  1);
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1.1,1);
	Vec2d<double> a2(1.1,0);
	Vec2d<double> a3(2  ,0);
	Vec2d<double> a4(2  ,1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( !r1.collision(r2) );
    }   
}

TEST_CASE( "Rectangle collision y-axis", "[Rectangle]")
{
    SECTION( "same angle overlap y-axis" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0, 0.5);
	Vec2d<double> a2(1, 0.5);
	Vec2d<double> a3(1, 2  );
	Vec2d<double> a4(0, 2 );

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "same angle y-axis, only collision in line segment" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,1);
	Vec2d<double> a2(1,1);
	Vec2d<double> a3(1,2);
	Vec2d<double> a4(0,2);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "same angle y-axis, no collision" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,10);
	Vec2d<double> a2(1,10);
	Vec2d<double> a3(1,11);
	Vec2d<double> a4(0,11);

	Rectangle<double> r2(a1, a2, a3, a4);

	CHECK( !r1.collision(r2) );
    }    

    SECTION( "different angle y-axis, deep collision" )
    {
	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0, 0.75);
	Vec2d<double> a2(1, 0.75);
	Vec2d<double> a3(0, 2);
	Vec2d<double> a4(1, 2);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "different angle y-axis, only collision in point" )
    {
	Vec2d<double> c1(0.5, 1 );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,1);
	Vec2d<double> a2(1,1);
	Vec2d<double> a3(1,2);
	Vec2d<double> a4(0,2);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "different angle y-axis, no collision far" )
    {
	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,10);
	Vec2d<double> a2(1,10);
	Vec2d<double> a3(1,20);
	Vec2d<double> a4(0,20);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( !r1.collision(r2) );
    }

    SECTION( "different angle y-axis, no collision close" )
    {
	Vec2d<double> c1(0.5,1 );
	Vec2d<double> c2(1 ,0.5);
	Vec2d<double> c3(0.5, 0);
	Vec2d<double> c4(0 ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,1.1);
	Vec2d<double> a2(1,1.1);
	Vec2d<double> a3(1,2  );
	Vec2d<double> a4(0,2  );

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( !r1.collision(r2) );
    }
}

TEST_CASE( "Rectangle general collision test", "[Rectangle]")
{
    SECTION( "both axis, deep collision" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0.75,0.75);
	Vec2d<double> a2(0.75,2   );
	Vec2d<double> a3(2,2      );
	Vec2d<double> a4(2,0.75   );

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "both axis, single point collision" )
    {
	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1,1);
	Vec2d<double> a2(1,2);
	Vec2d<double> a3(2,2);
	Vec2d<double> a4(2,1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( r1.collision(r2) );
    }

    SECTION( "both axis, almost collision" )
    {
	Vec2d<double> c1(0, 0);
	Vec2d<double> c2(1, 0);
	Vec2d<double> c3(1, 1);
	Vec2d<double> c4(0, 1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1.1, 1.1);
	Vec2d<double> a2(1.1, 2  );
	Vec2d<double> a3(2  , 2  );
	Vec2d<double> a4(2  , 1.1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( !r1.collision(r2) );
    }

    SECTION( "both rotated, verry close" )
    {
	Vec2d<double> c1(0,0.5);
	Vec2d<double> c2(0.5,1);
	Vec2d<double> c3(1,0.5);
	Vec2d<double> c4(0.5,0);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0.75,0);
	Vec2d<double> a2(1.25,0.5);
	Vec2d<double> a3(1.75,0);
	Vec2d<double> a4(1.25,-0.5);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	CHECK( !r1.collision(r2) );
    }
}
