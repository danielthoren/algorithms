#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "../vec2d.h"
#include "../line.h"
#include "../polygon.h"

using namespace dalg;


TEST_CASE( "Polygon Constructor test", "[Polygon]")
{    
    SECTION( "normal construction" )
    {
	Vec2d<int> p1(0, 0);
	Vec2d<int> p2(1, 1);
	Vec2d<int> p3(1, -1);
	std::vector<Vec2d<int>> pts{p1, p2, p3};

	Polygon poly(pts);
	
	std::vector<Vec2d<int>>& points = poly.get_points();

	REQUIRE( points[0] == p1 );
	REQUIRE( points[1] == p2 );
	REQUIRE( points[2] == p3 );
    }

    SECTION( "copy constructor" )
    {
	Vec2d<int> p1(1, -1);
	Vec2d<int> p2(0, 1);
	Vec2d<int> p3(1, 1);
	Vec2d<int> p4(-10, -10);
	std::vector<Vec2d<int>> pts{p1, p2, p3, p4};

	Polygon poly(pts);
	
	std::vector<Vec2d<int>>& points = poly.get_points();

	REQUIRE( points[0] == p1 );
	REQUIRE( points[1] == p2 );
	REQUIRE( points[2] == p3 );
	REQUIRE( points[3] == p4 );

	Polygon copy{poly};
	
	std::vector<Vec2d<int>>& copy_points = copy.get_points();

	REQUIRE( copy_points[0] == p1 );
	REQUIRE( copy_points[1] == p2 );
	REQUIRE( copy_points[2] == p3 );
	REQUIRE( copy_points[3] == p4 );
	
    }
}

TEST_CASE( "Polygon add_point test" )
{
    SECTION( "Test add_point" )
    {
	Vec2d<int> p1(0, 0);
	Vec2d<int> p2(1, 1);
	Vec2d<int> p3(1, -1);
	std::vector<Vec2d<int>> pts{p1, p2, p3};

	Polygon poly(pts);
	
	std::vector<Vec2d<int>>& points = poly.get_points();

	REQUIRE( points[0] == p1 );
	REQUIRE( points[1] == p2 );
	REQUIRE( points[2] == p3 );
	
	dalg::Vec2d<int> p4(4,0);

	poly.add_point(p4, 1);
	std::vector<Vec2d<int>>& n_points = poly.get_points();

	CHECK( n_points[0] == p1 );
	CHECK( n_points[1] == p2 );
	CHECK( n_points[2] == p4 );
	CHECK( n_points[3] == p3 );
    }
}

TEST_CASE( "Polygon area test", "[Polygon]" )
{
    SECTION( "Normal area test 1" )
    {
	dalg::Vec2d<int> p1(0, 0);
	dalg::Vec2d<int> p2(1, 1);	
	dalg::Vec2d<int> p3(4, 0);
	dalg::Vec2d<int> p4(1, -1);
	std::vector<dalg::Vec2d<int>> pts{p1, p2, p3, p4};

	dalg::Polygon poly(pts);

	CHECK( std::abs(poly.get_area<long double>()) == Approx(4.0).epsilon(0.01) );
    }

    SECTION( "Normal area test 2" )
    {
	dalg::Vec2d<int> p1(0, 0);
	dalg::Vec2d<int> p2(10, 0);
	dalg::Vec2d<int> p3(0, 10);
	
	std::vector<dalg::Vec2d<int>> pts{p1, p2, p3};

	dalg::Polygon poly(pts);

	CHECK( std::abs(poly.get_area<long double>()) == Approx(50.0).epsilon(0.01) );
    }

    SECTION( "Large area negative cords test" )
    {	
	dalg::Vec2d<int> p1(41, -6);
	dalg::Vec2d<int> p2(-24, -74);
	dalg::Vec2d<int> p3(-51, -6);
	dalg::Vec2d<int> p4(73, 17);
	dalg::Vec2d<int> p5(-30, -34);
	
	std::vector<dalg::Vec2d<int>> pts{p1, p2, p3, p4, p5};

	dalg::Polygon poly(pts);

	CHECK( std::abs(poly.get_area<long double>()) == Approx(3817.5).epsilon(0.01) );
    }

    SECTION( "Zero area one point test" )
    {
	dalg::Vec2d<int> p1(0,0);
	
	std::vector<dalg::Vec2d<int>> pts{p1};

	dalg::Polygon poly(pts);

	CHECK( std::abs(poly.get_area<long double>()) == Approx(0.0).epsilon(0.01) );
    }

    SECTION( "Zero area two point test" )
    {
	dalg::Vec2d<int> p1(0,0);
	dalg::Vec2d<int> p2(0,0);
	
	std::vector<dalg::Vec2d<int>> pts{p1, p2};

	dalg::Polygon poly(pts);

	CHECK( std::abs(poly.get_area<long double>()) == Approx(0.0).epsilon(0.01) );
    }   
}


TEST_CASE( "Polygon-LineSegment min_distance test", "[Polygon]" )
{
    SECTION( "Endpoints not closest" )
    {
	dalg::Vec2d<double> p1(0, 0);
	dalg::Vec2d<double> p2(1, 1);	
	dalg::Vec2d<double> p3(4, 0);
	dalg::Vec2d<double> p4(1, -1);
	std::vector<dalg::Vec2d<double>> pts{p1, p2, p3, p4};

	dalg::Polygon poly(pts);

	dalg::Vec2d<double> pt1(0.5, 2);
	dalg::Vec2d<double> pt2(1.5, 2);
	dalg::LineSegment<double> seg(pt1, pt2);

	auto res = poly.min_distance(seg);

	double dist = (res.first - res.second).length();

	CHECK( dist == Approx(1.0).epsilon(0.01) );
	CHECK( res.first == p2 );
	CHECK( res.second == Vec2d<double>{1,2} );
    }

    SECTION( "start point closest" )
    {
	dalg::Vec2d<double> p1(0, 0);
	dalg::Vec2d<double> p2(1, 1);	
	dalg::Vec2d<double> p3(4, 0);
	dalg::Vec2d<double> p4(1, -1);
	std::vector<dalg::Vec2d<double>> pts{p1, p2, p3, p4};

	dalg::Polygon poly(pts);

	dalg::Vec2d<double> pt1(5, 0);
	dalg::Vec2d<double> pt2(6, 0);
	dalg::LineSegment<double> seg(pt1, pt2);

	auto res = poly.min_distance(seg);

	double dist = (res.first - res.second).length();

	CHECK( dist == Approx(1.0).epsilon(0.01) );
	CHECK( res.first == p3 );
	CHECK( res.second == pt1 );
    }

    SECTION( "end point closest" )
    {
	dalg::Vec2d<double> p1(0, 0);
	dalg::Vec2d<double> p2(1, 1);	
	dalg::Vec2d<double> p3(4, 0);
	dalg::Vec2d<double> p4(1, -1);
	std::vector<dalg::Vec2d<double>> pts{p1, p2, p3, p4};

	dalg::Polygon poly(pts);

	dalg::Vec2d<double> pt1(6, 0);
	dalg::Vec2d<double> pt2(5, 0);
	dalg::LineSegment<double> seg(pt1, pt2);

	auto res = poly.min_distance(seg);

	double dist = (res.first - res.second).length();

	CHECK( dist == Approx(1.0).epsilon(0.01) );
	CHECK( res.first == p3 );
	CHECK( res.second == pt2 );
    }

    //TODO: Calculated the correct answer incorrectly, needs manual calculation
    // SECTION( "parallel line precision test" )
    // {
    // 	dalg::Vec2d<long double> p1(0, 0);
    // 	dalg::Vec2d<long double> p2(1, 1);	
    // 	dalg::Vec2d<long double> p3(4, 0);
    // 	dalg::Vec2d<long double> p4(1, -1);
    // 	std::vector<dalg::Vec2d<long double>> pts{p1, p2, p3, p4};

    // 	dalg::Polygon poly(pts);

    // 	dalg::Vec2d<long double> pt1(3, -5.0/6.0);
    // 	dalg::Vec2d<long double> pt2(1, -3.0/2.0);
    // 	dalg::LineSegment<long double> seg(pt1, pt2);

    // 	auto res = poly.min_distance(seg);

    // 	long double dist = (res.first - res.second).length();

    // 	CHECK( dist == Approx(0.5).epsilon(0.01) );
    // 	CHECK( res.first == p4 );
    // 	CHECK( res.second == pt2 );
    // }
}

TEST_CASE( "Polygon-Polygon min_distance test", "[Polygon]" )
{

    SECTION( "Small square in larger square" )
    {
	dalg::Vec2d<double> ip1(-5, -5);
	dalg::Vec2d<double> ip2(5, -5);	
	dalg::Vec2d<double> ip3(5, 5);
	dalg::Vec2d<double> ip4(-5, 5);

	std::vector<dalg::Vec2d<double>> ipts{ip1, ip2, ip3, ip4};
	dalg::Polygon inner(ipts);

	dalg::Vec2d<double> op1(-10, -10);
	dalg::Vec2d<double> op2(-10, 10);	
	dalg::Vec2d<double> op3(10, 10);
	dalg::Vec2d<double> op4(10, -10);

	std::vector<dalg::Vec2d<double>> opts{op1, op2, op3, op4};
	dalg::Polygon outer(opts);

	auto res = inner.min_distance(outer);

	double dist = (res.first - res.second).length();

	CHECK( dist == Approx(5).epsilon(0.01) );
    }

    SECTION( "Small square in larger square rotated 45" )
    {
	dalg::Vec2d<double> ip1(-5, -5);
	dalg::Vec2d<double> ip2(5, -5);	
	dalg::Vec2d<double> ip3(5, 5);
	dalg::Vec2d<double> ip4(-5, 5);

	std::vector<dalg::Vec2d<double>> ipts{ip1, ip2, ip3, ip4};
	dalg::Polygon inner(ipts);

	dalg::Vec2d<double> op1(0, 2.5);
	dalg::Vec2d<double> op2(2.5, 0);	
	dalg::Vec2d<double> op3(0, -2.5);
	dalg::Vec2d<double> op4(-2.5, 0);

	std::vector<dalg::Vec2d<double>> opts{op1, op2, op3, op4};
	dalg::Polygon outer(opts);

	auto res = inner.min_distance(outer);

	double dist = (res.first - res.second).length();

	CHECK( dist == Approx( 2.5 ).epsilon(0.01) );
    }

    SECTION( "Small square in larger square rotated 45 intersecting" )
    {
	dalg::Vec2d<double> ip1(-5, -5);
	dalg::Vec2d<double> ip2(5, -5);	
	dalg::Vec2d<double> ip3(5, 5);
	dalg::Vec2d<double> ip4(-5, 5);

	std::vector<dalg::Vec2d<double>> ipts{ip1, ip2, ip3, ip4};
	dalg::Polygon inner(ipts);

	dalg::Vec2d<double> op1(0, 5);
	dalg::Vec2d<double> op2(5, 0);	
	dalg::Vec2d<double> op3(0, -5);
	dalg::Vec2d<double> op4(-5, 0);

	std::vector<dalg::Vec2d<double>> opts{op1, op2, op3, op4};
	dalg::Polygon outer(opts);

	auto res = inner.min_distance(outer);

	double dist = (res.first - res.second).length();

	CHECK( dist == Approx( 0 ).epsilon(0.01) );
    }

    SECTION( "Triangle inside warped square" )
    {
	dalg::Vec2d<double> ip1(0,0);
	dalg::Vec2d<double> ip2(1,0);	
	dalg::Vec2d<double> ip3(1,1);

	std::vector<dalg::Vec2d<double>> ipts{ip1, ip2, ip3};
	dalg::Polygon inner(ipts);

	dalg::Vec2d<double> op1(3, -3);
	dalg::Vec2d<double> op2(3, 3);	
	dalg::Vec2d<double> op3(-4, 2);
	dalg::Vec2d<double> op4(-1, -1);
	dalg::Vec2d<double> op5(-2, -2);

	std::vector<dalg::Vec2d<double>> opts{op1, op2, op3, op4, op5};
	dalg::Polygon outer(opts);

	auto res = inner.min_distance(outer);

	double dist = (res.first - res.second).length();
	
	CHECK( dist == Approx( std::sqrt(2) ).epsilon(0.01) );
    }    
}
