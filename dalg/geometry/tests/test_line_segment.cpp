#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#include "../vec2d.h"
#include "../line_segment.h"
#include "../aabb.h"

#define DEBUG 1

using namespace dalg;


TEST_CASE( "LineSegment Vec2d constructor test", "[LineSegment]" )
{
    SECTION( "Vec2d constructor {0,0}->{1,1}" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	LineSegment<double> l1{p1,p2};

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{1,1} );
	REQUIRE( l1.get_end() == Vec2d<double>{1,1} );
    }

    SECTION( "Vec2d constructor {1,1}->{2,2}" )
    {
	Vec2d<double> p1{1, 1};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1,p2};

	REQUIRE( l1.get_start() == Vec2d<double>{1,1} );
	REQUIRE( l1.get_vec() == Vec2d<double>{1,1} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );
    }

    SECTION( "Vec2d constructor {0,1}->{2,2}" )
    {
	Vec2d<double> p1{0, 1};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1,p2};

	REQUIRE( l1.get_start() == Vec2d<double>{0,1} );
	REQUIRE( l1.get_vec() == Vec2d<double>{2,1} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );
    }

    SECTION( "Vec2d constructor {1,0}->{2,2}" )
    {
	Vec2d<double> p1{1, 0};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1,p2};

	REQUIRE( l1.get_start() == Vec2d<double>{1,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{1,2} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );
    }

    SECTION( "Vec2d constructor {0,0}->{0,2}" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{0, 2};

	LineSegment<double> l1{p1,p2};

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{0,2} );
	REQUIRE( l1.get_end() == Vec2d<double>{0,2} );
    }

    SECTION( "Vec2d constructor {0,0}->{2,0}" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 0};

	LineSegment<double> l1{p1,p2};

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{2,0} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,0} );	
    }
}

TEST_CASE( "LineSegment Scalar constructor test" )
    {

    SECTION( "Scalar constructor {0,0}->{1,1}" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{1, 1};

	LineSegment<double> l1{p1.x, p1.y, p2.x, p2.y};

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{1,1} );
	REQUIRE( l1.get_end() == Vec2d<double>{1,1} );
    }

    SECTION( "Scalar constructor {1,1}->{2,2}" )
    {
	Vec2d<double> p1{1, 1};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1.x, p1.y, p2.x, p2.y};

	REQUIRE( l1.get_start() == Vec2d<double>{1,1} );
	REQUIRE( l1.get_vec() == Vec2d<double>{1,1} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );
    }

    SECTION( "Scalar constructor {0,1}->{2,2}" )
    {
	Vec2d<double> p1{0, 1};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1.x, p1.y, p2.x, p2.y};

	REQUIRE( l1.get_start() == Vec2d<double>{0,1} );
	REQUIRE( l1.get_vec() == Vec2d<double>{2,1} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );
    }

    SECTION( "Scalar constructor {1,0}->{2,2}" )
    {
	Vec2d<double> p1{1, 0};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1.x, p1.y, p2.x, p2.y};

	REQUIRE( l1.get_start() == Vec2d<double>{1,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{1,2} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );
    }

    SECTION( "Scalar constructor {0,0}->{0,2}" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{0, 2};

	LineSegment<double> l1{p1.x, p1.y, p2.x, p2.y};

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{0,2} );
	REQUIRE( l1.get_end() == Vec2d<double>{0,2} );
    }

    SECTION( "Scalar constructor {0,0}->{2,0}" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 0};

	LineSegment<double> l1{p1.x, p1.y, p2.x, p2.y};

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{2,0} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,0} );	
    }
}

TEST_CASE( "LineSegment Copy constructor test", "[LineSegment]" )
{
    SECTION( "Normal copy construction" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1, p2};
	LineSegment<double> l2{l1};

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{2,2} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );

	REQUIRE( l2.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l2.get_vec() == Vec2d<double>{2,2} );
	REQUIRE( l2.get_end() == Vec2d<double>{2,2} );

	REQUIRE( l1 == l2 );
    }
}

TEST_CASE( "LineSegment comparison test", "[LineSegment]" )
{
    SECTION( "normal comparison posetive" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};	
	
	LineSegment<double> l1{p1, p2};
	LineSegment<double> l2{p1, p2};

	CHECK( l1 == l2 );
	CHECK_FALSE( l1 != l2 );
    }

    SECTION( "normal comparison negative" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};	
	
	LineSegment<double> l1{p1, p2};

	Vec2d<double> p3{0, 0};
	Vec2d<double> p4{2, 3};
	
	LineSegment<double> l2{p3, p4};

	CHECK_FALSE( l1 == l2 );
	CHECK( l1 != l2 );
    }

    SECTION( "close comparison negative" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};	
	
	LineSegment<double> l1{p1, p2};

	Vec2d<double> p3{0, 0};
	Vec2d<double> p4{2, 2.001};
	
	LineSegment<double> l2{p3, p4};

	CHECK_FALSE( l1 == l2 );
	CHECK( l1 != l2 );
    }

    SECTION( "point comparison posetive" )
    {
	Vec2d<double> p1{0, 0};
	
	LineSegment<double> l1{p1, p1};	
	LineSegment<double> l2{p1, p1};

	CHECK( l1 == l2 );
	CHECK_FALSE( l1 != l2 );
    }

    SECTION( "point comparison negative" )
    {
	Vec2d<double> p1{0, 0};
	
	LineSegment<double> l1{p1, p1};

	Vec2d<double> p2{0, 1};
	
	LineSegment<double> l2{p2, p2};

	CHECK_FALSE( l1 == l2 );
	CHECK( l1 != l2 );
    }

    SECTION( "point comparison close negative" )
    {
	Vec2d<double> p1{0, 0};
	
	LineSegment<double> l1{p1, p1};

	Vec2d<double> p2{0, 0.001};
	
	LineSegment<double> l2{p2, p2};

	CHECK_FALSE( l1 == l2 );
	CHECK( l1 != l2 );
    }

    SECTION( "comparison with self negative" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};
	
	LineSegment<double> l1{p1, p2};

	CHECK( l1 == l1 );
	CHECK_FALSE( l1 != l1 );
    }

    SECTION( "point comparison with self negative" )
    {
	Vec2d<double> p1{0, 0};
	
	LineSegment<double> l1{p1, p1};

	CHECK( l1 == l1 );
	CHECK_FALSE( l1 != l1 );
    }
}

TEST_CASE( "LineSegment assignment test", "[LineSegment]" )
{
    SECTION( "Normal assignment" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1, p2};
	LineSegment<double> l2 = l1;

	CHECK( l1.get_start() == Vec2d<double>{0,0} );
	CHECK( l1.get_vec() == Vec2d<double>{2,2} );
	CHECK( l1.get_end() == Vec2d<double>{2,2} );

	CHECK( l2.get_start() == Vec2d<double>{0,0} );
	CHECK( l2.get_vec() == Vec2d<double>{2,2} );
	CHECK( l2.get_end() == Vec2d<double>{2,2} );

	CHECK( l1 == l2 );
    }

    SECTION( "assign to self" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1, p2};
	l1 = l1;

	CHECK( l1.get_start() == Vec2d<double>{0,0} );
	CHECK( l1.get_vec() == Vec2d<double>{2,2} );
	CHECK( l1.get_end() == Vec2d<double>{2,2} );
    }
}

TEST_CASE( "LineSegment closest_points test", "[LineSegment]" )
{
    SECTION( "Kattis test (1)" )
    {
	LineSegment<double> l1{-10, 0, 10, 0};
	LineSegment<double> l2{0, -10, 0, 10};

	auto res = l1.closest_points(l2);

	CHECK( (res.first - res.second).length() < 0.0001 );
    }
    
    SECTION( "Kattis test (2)" )
    {
	LineSegment<double> l1{-10, 0, 10, 0};
	LineSegment<double> l2{-5, 0, 5, 0};

	auto res = l1.closest_points(l2);

	CHECK( (res.first - res.second).length() < 0.0001 );
    }

    SECTION( "Kattis test (3)" )
    {
	LineSegment<double> l1{1, 1, 1, 1};
	LineSegment<double> l2{1, 1, 2, 1};

	auto res = l1.closest_points(l2);

	CHECK( (res.first - res.second).length() < 0.0001 );
    }

    SECTION( "Kattis test (4)" )
    {
	LineSegment<double> l1{1, 1, 1, 1};
	LineSegment<double> l2{2, 1, 2, 1};

	auto res = l1.closest_points(l2);

	CHECK( 1 - (res.first - res.second).length() < 0.0001 );
    }

    SECTION( "Kattis test (5)" )
    {
	LineSegment<double> l1{1871, 5789, 216, -517};
	LineSegment<double> l2{189, -1518, 3851, 1895};

	auto res = l1.closest_points(l2);

	CHECK( 713.86 - (res.first - res.second).length() < 0.0001 );
    }    
}

TEST_CASE( "LineSegment on_line test", "[LineSegment]" )
{
    SECTION( "on line between points posetive" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{2,2};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{1,1};

	CHECK( line.on_line(pt) );
    }

    SECTION( "on line posetive" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{2,2};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{4,4};

	CHECK( line.on_line(pt) );
    }

    SECTION( "on line between points negative" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{-2,-2};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{-1,-1};

	CHECK( line.on_line(pt) );
    }
    
    SECTION( "on line negative" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{-2,-2};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{-4,-4};

	CHECK( line.on_line(pt) );
    }

    SECTION( "on the point p + u" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{1,1};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{1,1};

	CHECK( line.on_line(pt) );
    }

    SECTION( "on the point p" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{1,1};

	LineSegment<double> line{p1, p2};
      
	Vec2d<double> pt{0,0};
      
	CHECK( line.on_line(pt) );
    }
    
    SECTION( "not on line" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{0,1};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{1,1};

	CHECK_FALSE( line.on_line(pt) );
    }

    SECTION( "not on line, so close that precision makes on line" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{0,1};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{0.00001,0.5};

	CHECK( line.on_line(pt) );
    }

    SECTION( "not on line, close (1)" )
    {
	Vec2d<double> p1{0,0, 0};
	Vec2d<double> p2{0,1, 0};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{0.1, 0.5, 0};

	CHECK_FALSE( line.on_line(pt) );
    }

    SECTION( "not on line, close (2)" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{0,1};

	LineSegment<double> line{p1, p2, 0.0};

	Vec2d<double> pt{0.0001,1, 0.0};

	CHECK_FALSE( line.on_line(pt) );
    }
}

TEST_CASE( "LineSegment on_line_segment test", "[LineSegment]" )
{
    SECTION( "on line posetive" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{2,2};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{1,1};

	CHECK( line.on_segment(pt) );
    }


    SECTION( "on line negative" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{-2,-2};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{-1,-1};

	CHECK( line.on_segment(pt) );
    }

    SECTION( "on end edge of line" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{1,1};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{1,1};

	CHECK( line.on_segment(pt) );
    }

    SECTION( "on start edge of line" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{1,1};

	LineSegment<double> line{p1, p2};
      
	Vec2d<double> pt{0,0};
      
	CHECK( line.on_segment(pt) );
    }
    
    SECTION( "not on line" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{0,1};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{1,1};

	CHECK_FALSE( line.on_segment(pt) );
    }

    SECTION( "not on line, so close that precision makes on line" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{0,1};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{0.0,1.0001};

	CHECK_FALSE( line.on_segment(pt) );
    }

    SECTION( "not on line, close (1) Also tests vec2d == operator" )
    {
	Vec2d<double> p1{0, 0, 0};
	Vec2d<double> p2{0, 1, 0};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{0.0, 1 + DEFAULT_PREC, 0.0};

	CHECK_FALSE( line.on_segment(pt) );
    }

    SECTION( "not on line, close (2)" )
    {
	Vec2d<double> p1{0, 0, 0.0};
	Vec2d<double> p2{0, 1, 0.0};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{DEFAULT_PREC, 1, 0.0};

	CHECK_FALSE( line.on_segment(pt) );
    }
}


TEST_CASE( "LineSegment intersection test", "[LineSegment]" )
{
    SECTION( "kattis test 1" )
    {
	Vec2d<double> p1{-10, 0};
	Vec2d<double> p2{10, 0};

	LineSegment<double> l1{p1, p2};
      
	Vec2d<double> q1{0, -10};
	Vec2d<double> q2{0, 10};

	LineSegment<double> l2{q1, q2};

	auto res = l1.intersect(l2);

	CHECK( std::holds_alternative<dalg::Vec2d<double>>(res) );

	if (std::holds_alternative<dalg::Vec2d<double>>(res))
	{
	    dalg::Vec2d<double> act = std::get<dalg::Vec2d<double>>(res);
	    CHECK( act == Vec2d<double>{0.0, 0.0} );
	}
    }

    SECTION( "kattis test 2" )
    {
	Vec2d<double> p1{-10, 0};
	Vec2d<double> p2{10, 0};
      
	LineSegment<double> l1{p1, p2};
      
	Vec2d<double> q1{-5, 0};
	Vec2d<double> q2{5, 0};

	LineSegment<double> l2{q1, q2};

	auto res = l1.intersect(l2);
      
	CHECK( std::holds_alternative<LineSegment<double>>(res) );

	if (std::holds_alternative<LineSegment<double>>(res))
	{
	    LineSegment<double> act =
		std::get<LineSegment<double>>(res);
	  
	    CHECK( act.get_start() == Vec2d<double>{-5.0, 0.0} );
	    CHECK( act.get_end() == Vec2d<double>{5.0, 0.0} );
	}
    }

    SECTION( "kattis test 3" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{1,1};

	LineSegment<double> l1{p1, p2};
      
	Vec2d<double> q1{1,1};
	Vec2d<double> q2{2,1};

	LineSegment<double> l2{q1, q2};

	auto res = l1.intersect(l2);

	CHECK( std::holds_alternative<dalg::Vec2d<double>>(res) );

	if (std::holds_alternative<dalg::Vec2d<double>>(res))
	{
	    dalg::Vec2d<double> act = std::get<dalg::Vec2d<double>>(res);
	    CHECK( act == Vec2d<double>{1.0, 1.0} );
	}
    }

    SECTION( "kattis test 4" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{1,1};

	LineSegment<double> l1{p1, p2};
	
	Vec2d<double> q1{2,1};
	Vec2d<double> q2{2,1};

	LineSegment<double> l2{q1, q2};

	auto res = l1.intersect(l2);

	CHECK_FALSE( std::holds_alternative<Vec2d<double>>(res) );
	CHECK_FALSE( std::holds_alternative<LineSegment<double>>(res) );
    }

    SECTION( "kattis test 5" )
    {
	Vec2d<double> p1{1871, 5789};
	Vec2d<double> p2{216, -517};

	LineSegment<double> l1{p1, p2};
      
	Vec2d<double> q1{189, -518};
	Vec2d<double> q2{3851, 1895};

	LineSegment<double> l2{q1, q2};

	auto res = l1.intersect(l2);

	REQUIRE( std::holds_alternative<dalg::Vec2d<double>>(res) );

	dalg::Vec2d<double> act = std::get<dalg::Vec2d<double>>(res);
	CHECK( act == Vec2d<double>{221.33, -496.70, 0.05} );
    }
}

TEST_CASE( "get_aabb() test", "[LineSegment]" )
{
    SECTION( "Normal, posetive inclination" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{10, 10};

	LineSegment<double> l1{p1, p2};

	AABB<double> aabb{p1, p2};

	CHECK( l1.get_aabb() == aabb );
    }

    SECTION( "Normal, negative inclination" )
    {
	Vec2d<double> p1{0,0};
	Vec2d<double> p2{-10, 10};

	LineSegment<double> l1{p1, p2};

	AABB<double> aabb{p1, p2};

	CHECK( l1.get_aabb() == aabb );
    }

}
