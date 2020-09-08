#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#include "../circle.h"
#include "../line.h"
#include "../intersect.h"

#define DEBUG 1

using namespace dalg;

TEST_CASE( "Circle-circle intersection test", "[Intersection]" )
{
    SECTION( "Test edge intersection" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Circle<double> c2{Vec2d<double>{0,10}, 5};

	auto col = intersect<double>(c1, c2);

	REQUIRE( std::holds_alternative<Vec2d<double>>(col) );
	    
	Vec2d<double> res = std::get<Vec2d<double>>(col);
	
	CHECK( res == Vec2d<double>{0,5} );
    }

    SECTION( "Test complete intersection" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Circle<double> c2{Vec2d<double>{0,0}, 5};

	auto col = intersect<double>(c1, c2);

	REQUIRE( std::holds_alternative<Circle<double>>(col) );
	    
	Circle<double> res = std::get<Circle<double>>(col);

	Circle<double> ref {Vec2d<double>{0,0}, 5};
	
	CHECK( res == ref );
    }

    SECTION( "Test normal intersection" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 10};
	Circle<double> c2{Vec2d<double>{15,0}, 10};

	auto col = intersect<double>(c1, c2);

	REQUIRE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	
	std::pair<Vec2d<double>, Vec2d<double>> res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(col);

	CHECK( res.first == Vec2d<double>{225.0 / 30.0, -std::sqrt(100 - std::pow(225.0 / 30.0, 2))} );
	CHECK( res.second == Vec2d<double>{225.0 / 30.0, std::sqrt(100 - std::pow(225.0 / 30.0, 2))} );
    }    

}

TEST_CASE( "Circle-Line intersection test", "[Intersection]" )
{
    /*************************************************************/
    /* Tests with circle in origo                                */
    /*************************************************************/
    
    SECTION( "Test horizontal intersection circle in origo" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Line<double> l1{Vec2d<double>{0,0}, Vec2d<double>{1,0}};

	auto col = intersect<double>(c1, l1);

	REQUIRE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	    
	std::pair<Vec2d<double>, Vec2d<double>> res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(col);
	
	CHECK( res.first == Vec2d<double>{5,0} );
	CHECK( res.second == Vec2d<double>{-5,0} );
    }

    SECTION( "Test vertical intersection circle in origo" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Line<double> l1{Vec2d<double>{0,0}, Vec2d<double>{0,1}};

	auto col = intersect<double>(c1, l1);

	REQUIRE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	    
	std::pair<Vec2d<double>, Vec2d<double>> res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(col);
	
	CHECK( res.first == Vec2d<double>{0,5} );
	CHECK( res.second == Vec2d<double>{0,-5} );
    }

    SECTION( "Test sloped intersection circle in origo" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Line<double> l1{Vec2d<double>{0,0}, Vec2d<double>{1,1}};

	auto col = intersect<double>(c1, l1);

	REQUIRE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	    
	std::pair<Vec2d<double>, Vec2d<double>> res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(col);

	double x = c1.radius * std::cos(PI / 4);
	double y = c1.radius * std::sin(PI / 4);
	
	CHECK( res.first == Vec2d<double>{x, y} );
	CHECK( res.second == Vec2d<double>{-x, -y} );
    }

    SECTION( "Test sloped intersection reversed parameters circle in origo" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Line<double> l1{Vec2d<double>{0,0}, Vec2d<double>{1,1}};

	auto col = intersect<double>(l1, c1);

	REQUIRE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	    
	std::pair<Vec2d<double>, Vec2d<double>> res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(col);

	double x = c1.radius * std::cos(PI / 4);
	double y = c1.radius * std::sin(PI / 4);
	
	CHECK( res.first == Vec2d<double>{x, y} );
	CHECK( res.second == Vec2d<double>{-x, -y} );
    }

    SECTION( "Test sloped intersection opposite circle in origo" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Line<double> l1{Vec2d<double>{0,0}, Vec2d<double>{-1,1}};

	auto col = intersect<double>(c1, l1);

	REQUIRE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	    
	std::pair<Vec2d<double>, Vec2d<double>> res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(col);

	double x = c1.radius * std::cos(PI / 4);
	double y = c1.radius * std::sin(PI / 4);
	
	CHECK( res.first == Vec2d<double>{-x, y} );
	CHECK( res.second == Vec2d<double>{x, -y} );
    }

    SECTION( "Test no intersection circle in origo" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Line<double> l1{Vec2d<double>{10,10}, Vec2d<double>{1,0}};

	auto col = intersect<double>(c1, l1);

	CHECK_FALSE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	CHECK_FALSE( std::holds_alternative<Vec2d<double>>(col) );
    }

    SECTION( "Test tangent intersection circle in origo" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Line<double> l1{Vec2d<double>{5,0}, Vec2d<double>{0,1}};

	auto col = intersect<double>(c1, l1);

	REQUIRE( std::holds_alternative<Vec2d<double>>(col) );
	    
	Vec2d<double> res = std::get<Vec2d<double>>(col);
	
	CHECK( res == Vec2d<double>{5, 0} );
    }
    
    SECTION( "Test sloped intersection circle not in origo" )
    {
	Circle<double> c1{Vec2d<double>{5,5}, 5};
	Line<double> l1{Vec2d<double>{0,0}, Vec2d<double>{1,1}};

	auto col = intersect<double>(l1, c1);

	REQUIRE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	    
	std::pair<Vec2d<double>, Vec2d<double>> res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(col);

	double x = c1.radius * std::cos(PI / 4);
	double y = c1.radius * std::sin(PI / 4);       
	
	CHECK( res.first == Vec2d<double>{x + 5, y + 5} );
	CHECK( res.second == Vec2d<double>{(x + 5) - 2*x, (y + 5) - 2*y} );
    }

    SECTION( "Test x/y axis intersection" )
    {
	Circle<double> c1{Vec2d<double>{4,-1}, 4};
	Line<double> x_axis{Vec2d<double>{0,0}, Vec2d<double>{1,0}};
	Line<double> y_axis{Vec2d<double>{0,0}, Vec2d<double>{0,1}};

	auto x_col = intersect<double>(x_axis, c1);
	auto y_col = intersect<double>(y_axis, c1);

	REQUIRE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(x_col) );
	REQUIRE( std::holds_alternative<Vec2d<double>>(y_col) );
	    
	std::pair<Vec2d<double>, Vec2d<double>> x_res = std::get<std::pair<Vec2d<double>, Vec2d<double>>>(x_col);
	Vec2d<double> y_res = std::get<Vec2d<double>>(y_col);
	
	CHECK( x_res.first == Vec2d<double>{7.87, 0, 0.005} );
	CHECK( x_res.second == Vec2d<double>{0.127, 0, 0.005} );

	CHECK( y_res == Vec2d<double>{0, -1} );
    }    
    
}

TEST_CASE( "Line-Line intersection test", "[Intersection]" )
{
    SECTION( "Parallel lines" )
    {
	Line<double> l1{Vec2d<double>{0,0}, Vec2d<double>{10,10}};
	Line<double> l2{Vec2d<double>{0,5}, Vec2d<double>{10,10}};

	auto col = intersect<double>(l1, l2);

	CHECK_FALSE( std::holds_alternative<Vec2d<double>>(col) );
	CHECK_FALSE( std::holds_alternative<Line<double>>(col) );
    }

    SECTION( "Through origin" )
    {
	Line<double> l1{Vec2d<double>{0,0}, Vec2d<double>{1,1}};
	Line<double> l2{Vec2d<double>{0,0}, Vec2d<double>{1,2}};

	auto col = intersect<double>(l1, l2);

	REQUIRE( std::holds_alternative<Vec2d<double>>(col) );

	Vec2d<double> res = std::get<Vec2d<double>>(col);

	CHECK( res == Vec2d<double>{0,0} );
    }

    SECTION( "Same line" )
    {
	Line<double> l1{Vec2d<double>{10,10}, Vec2d<double>{100,100}};
	Line<double> l2{Vec2d<double>{0,0}, Vec2d<double>{10,10}};

	auto col = intersect<double>(l1, l2);

	REQUIRE( std::holds_alternative<Line<double>>(col) );

	Line<double> res = std::get<Line<double>>(col);

	CHECK( res == l1);
	CHECK( res == l2);
    }

    SECTION( "kattis test 1 (line segment)" )
    {
	Vec2d<double> p1{-10, 0};
	Vec2d<double> p2{10, 0};

	Line<double> l1{p1, p2};
      
	Vec2d<double> q1{0, -10};
	Vec2d<double> q2{0, 10};

	Line<double> l2{q1, q2};

	auto res = intersect(l1, l2);

	REQUIRE( std::holds_alternative<dalg::Vec2d<double>>(res) );
	
	dalg::Vec2d<double> act = std::get<dalg::Vec2d<double>>(res);
	CHECK( act == Vec2d<double>{0.0, 0.0} );
    }

    SECTION( "kattis test 2 (line segment)" )
    {
	Vec2d<double> p1{-10, 0};
	Vec2d<double> p2{10, 0};
      
	Line<double> l1{p1, p1 - p2};
      
	Vec2d<double> q1{-5, 0};
	Vec2d<double> q2{5, 0};

	Line<double> l2{q1, q1 - q2};

	auto res = intersect(l1, l2);
      
	REQUIRE( std::holds_alternative<Line<double>>(res) );

	Line<double> act =
	    std::get<Line<double>>(res);
	  
	CHECK( act == l1 );
    }

    SECTION( "kattis test 3 (line segment)" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{1,1};

	Line<double> l1{p1, p2};
      
	Vec2d<double> q1{1,1};
	Vec2d<double> q2{2,1};

	Line<double> l2{q1, q2};

	auto res = intersect(l1, l2);

	REQUIRE( std::holds_alternative<dalg::Vec2d<double>>(res) );

	dalg::Vec2d<double> act = std::get<dalg::Vec2d<double>>(res);
	CHECK( act == Vec2d<double>{1.0, 1.0} );
    }

    SECTION( "kattis test 5 (line segment)" )
    {
	Vec2d<double> p1{1871, 5789};
	Vec2d<double> p2{216, -517};

	Line<double> l1{p1, p1 - p2};
      
	Vec2d<double> q1{189, -518};
	Vec2d<double> q2{3851, 1895};

	Line<double> l2{q1, q1 - q2};

	auto res = intersect(l1, l2);

	REQUIRE( std::holds_alternative<dalg::Vec2d<double>>(res) );

	dalg::Vec2d<double> act = std::get<dalg::Vec2d<double>>(res);
	CHECK( act == Vec2d<double>{221.33, -496.70, 0.05} );
    }

}
