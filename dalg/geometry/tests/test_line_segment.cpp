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

TEST_CASE( "Vec2d line segment intersection test", "[Vec2d]" )
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
