#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#include "../vec2d.h"
#include "../line.h"
#include "../utility.h"

#define DEBUG 1

using namespace dalg;


TEST_CASE( "Constructor test", "[Line]" )
{
    SECTION( "Vec2d constructor {0,0}->{1,1}" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	REQUIRE( l1.p0 == Vec2d<double>{0,0} );
	REQUIRE( l1.u == Vec2d<double>{1,1} );
	REQUIRE( l1.prec == DEFAULT_PREC );
    }

    SECTION( "Floating pt constructor {0.01,0.01}->{-1.01,1.01} prec = 0.1" )
    {
	Vec2d<double> p1{0.01, 0.01};
	Vec2d<double> p2{-1.01, 1.01};

	Line<double> l1{p1,p2,0.1};

	REQUIRE( l1.p0 == Vec2d<double>{0.01,0.01} );
	REQUIRE( l1.u == Vec2d<double>{-1.01,1.01} );
	REQUIRE( l1.prec == 0.1 );
    }
}

TEST_CASE( "Equality test", "[Line]" )
{
    SECTION( "Equal" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> q1{-10, -10};
	Vec2d<double> q2{0, 0};

	Line<double> l2{q1,q2};

	CHECK( l1 == l2 );
	CHECK_FALSE( l1 != l2 );
    }

    SECTION( "Not equal" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> q1{10, -10};
	Vec2d<double> q2{0, 0};

	Line<double> l2{q1,q2};

	CHECK_FALSE( l1 == l2 );
	CHECK( l1 != l2 );
    }

    SECTION( "Prec test, Equal" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> q1{0, 0 + (DEFAULT_PREC / 2)};
	Vec2d<double> q2{1, 1};

	Line<double> l2{q1,q2};

	CHECK( l1 == l2 );
	CHECK_FALSE( l1 != l2 );
    }

    SECTION( "Prec test, Not equal" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> q1{0, 0 + DEFAULT_PREC};
	Vec2d<double> q2{1, 1};

	Line<double> l2{q1,q2};

	CHECK_FALSE( l1 == l2 );
	CHECK( l1 != l2 );
    }
}


TEST_CASE( "Parallel test", "[Line]" )
{
    SECTION( "Parallel" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> q1{528.8, 3046.882};
	Vec2d<double> q2{10, 10};

	Line<double> l2{q1,q2};

	CHECK( parallel(l1, l2) );
    }

    SECTION( "Not Parallel" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> q1{0, 0};
	Vec2d<double> q2{1, 2};

	Line<double> l2{q1,q2};

	CHECK_FALSE( parallel(l1, l2) );
    }

    SECTION( "Precision test, Parallel" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> q1{528.8, 3046.882};
	Vec2d<double> q2{10, 10 + (DEFAULT_PREC / 2)};

	Line<double> l2{q1,q2};

	CHECK( parallel(l1, l2) );
    }

    SECTION( "Precision test, Not Parallel" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> q1{0, 0};
	Vec2d<double> q2{1, 1 + DEFAULT_PREC*2};

	Line<double> l2{q1,q2};

	CHECK_FALSE( parallel(l1, l2) );
    }
}

TEST_CASE( "Project test", "[Line]" )
{
    SECTION( "To origo" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	Line<double> l1{p1,p2};

	Vec2d<double> pt{-1, 1};

	CHECK( project(pt, l1) == Vec2d<double>{0,0} );
    }

    SECTION( "Test 2" )
    {
	Vec2d<double> p0{0, -5};
	Vec2d<double> p_tmp{3, 0};
	Vec2d<double> u{ p0 - p_tmp };	

	Line<double> l1{p0, u};

	Vec2d<double> pt{-4, 5};

	CHECK( project(pt, l1) == Vec2d<double>{57.0/17.0, 10.0/17.0} );
    }

    SECTION( "Test 2" )
    {
	Vec2d<double> p0{0, 0};
	Vec2d<double> u{1, 2};	

	Line<double> l1{p0, u};

	Vec2d<double> pt{2, 3};

	CHECK( project(pt, l1) == Vec2d<double>{8.0/5.0, 16.0/5.0} );
    }
}
