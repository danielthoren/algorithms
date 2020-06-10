#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#include "../circle.h"
#include "../line.h"
#include "../collision.h"

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
	Line<double> l1{Vec2d<double>{10,10}, Vec2d<double>{11,10}};

	auto col = intersect<double>(c1, l1);

	CHECK_FALSE( std::holds_alternative<std::pair<Vec2d<double>, Vec2d<double>>>(col) );
	CHECK_FALSE( std::holds_alternative<Vec2d<double>>(col) );
    }

    SECTION( "Test tangent intersection circle in origo" )
    {
	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Line<double> l1{Vec2d<double>{5,0}, Vec2d<double>{5,1}};

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
