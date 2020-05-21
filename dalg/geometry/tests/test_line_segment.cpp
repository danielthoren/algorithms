#include "catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#include "../vec2d.h"
#include "../line_segment.h"

#define DEBUG 1

using namespace dalg;


TEST_CASE( "LineSegment Vec2d constructor test" )
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

TEST_CASE( "LineSegment Copy constructor test" )
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

TEST_CASE( "LineSegment comparison test" )
{

}

TEST_CASE( "LineSegment assignment test" )
{
    SECTION( "Normal assignment" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1, p2};
	LineSegment<double> l2 = l1;

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{2,2} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );

	REQUIRE( l2.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l2.get_vec() == Vec2d<double>{2,2} );
	REQUIRE( l2.get_end() == Vec2d<double>{2,2} );

	REQUIRE( l1 == l2 );
    }

    SECTION( "assign to self" )
    {
	Vec2d<double> p1{0, 0};
	Vec2d<double> p2{2, 2};

	LineSegment<double> l1{p1, p2};
	l1 = l1;

	REQUIRE( l1.get_start() == Vec2d<double>{0,0} );
	REQUIRE( l1.get_vec() == Vec2d<double>{2,2} );
	REQUIRE( l1.get_end() == Vec2d<double>{2,2} );
    }
}

TEST_CASE( "LineSegment closest_point test" )
{

}

TEST_CASE( "LineSegment closest_points test" )
{

}

TEST_CASE( "LineSegment on_line test", "[Vec2d]" )
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
	Vec2d<double> p1{0,0, 0.0};
	Vec2d<double> p2{0,1, 0.0};

	LineSegment<double> line{p1, p2};

	Vec2d<double> pt{0.0001,1, 0.0};

	CHECK_FALSE( line.on_line(pt) );
    }
}

TEST_CASE( "LineSegment on_line_segment test" )
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


TEST_CASE( "LineSegment line segment intersection test", "[Vec2d]" )
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

	CHECK( std::holds_alternative<dalg::Vec2d<double>>(res) );

	if (std::holds_alternative<dalg::Vec2d<double>>(res))
	{
	    dalg::Vec2d<double> act = std::get<dalg::Vec2d<double>>(res);
	    CHECK( act == Vec2d<double>{221.33, -496.70, 0.05} );
	}
    }
}
