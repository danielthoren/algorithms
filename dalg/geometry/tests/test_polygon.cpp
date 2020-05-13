#include "catch.hpp"

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
    dalg::Vec2d<int> p1(0, 0);
    dalg::Vec2d<int> p2(1, 1);
    dalg::Vec2d<int> p3(1, -1);
    std::vector<dalg::Vec2d<int>> pts{p1, p2, p3};

    dalg::Polygon poly(pts);
    
    SECTION( "Test normal construction" )
    {
	std::vector<dalg::LineSegment<int>>& segments = poly.get_segments();

	REQUIRE( segments[0].get_start_point() == p1 );
	REQUIRE( segments[0].get_end_point() == p2 );
	REQUIRE( segments[1].get_start_point() == p2 );
	REQUIRE( segments[1].get_end_point() == p3 );
	REQUIRE( segments[2].get_start_point() == p3 );
	REQUIRE( segments[2].get_end_point() == p1 );
    }

    SECTION( "Test add_point" )
    {
	dalg::Vec2d<int> p4(4,0);

	poly.add_point(p4, 1);
	std::vector<dalg::LineSegment<int>>& segments = poly.get_segments();

	CHECK( segments[0].get_start_point() == p1 );
	CHECK( segments[0].get_end_point() == p2 );
	CHECK( segments[1].get_start_point() == p2 );
	CHECK( segments[1].get_end_point() == p4 );
	CHECK( segments[2].get_start_point() == p4 );
	CHECK( segments[2].get_end_point() == p3 );
	CHECK( segments[3].get_start_point() == p3 );
	CHECK( segments[3].get_end_point() == p1 );
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


TEST_CASE( "Polygon min_distance test", "[Polygon]" )
{
    SECTION( "Normal poly distance" )
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
    }

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
