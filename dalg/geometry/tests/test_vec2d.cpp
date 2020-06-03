#include "../../../catch.hpp"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "../vec2d.h"
#include "../utility.h"

#define DEBUG 1

using namespace dalg;

TEST_CASE( "Vec2d Constructor test", "[Vec2d]")
{
    SECTION( "copy constructor" )
    {
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};

	REQUIRE( p2.x == p1.x );
	REQUIRE( p2.y == p1.y );
        REQUIRE( p2 == p1 );	
    }
}

TEST_CASE( "Vec2d addition test", "[Vec2d]")
{
    SECTION( "Vec2d + Vec2d" )
    {
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
	
	Vec2d<int> p3{p1 + p2};

	CHECK( p3.x == p1.x + p2.x );
	CHECK( p3.y == p1.y + p2.y );
    }

    SECTION( "Vec2d += Vec2d" )
    {
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
	
	p2 += p1;

	CHECK( p2.x == 2 );
	CHECK( p2.y == 2 );
	CHECK( p1.x == 1 );
	CHECK( p1.y == 1 );
    }
}

TEST_CASE( "Vec2d substraction test", "[Vec2d]")
{
    SECTION( "Vec2d - Vec2d" )
    {
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
	
	Vec2d<int> p3{p1 - p2};

	CHECK( p3.x == p1.x - p2.x );
	CHECK( p3.y == p1.y - p2.y );
    }

    SECTION( " Vec2d -= Vec2d" )
    {
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
	
	p2 -= p1;

        CHECK( p2.x == 0 );
	CHECK( p2.y == 0 );
	CHECK( p1.x == 1 );
	CHECK( p1.y == 1 );
    }
}

TEST_CASE( "Vec2d length test", "[Vec2d]")
{
    SECTION( "normal length (1)" )
    {
	Vec2d<int> p1{1,1};
	
	double len{p1.length()};
	CHECK( len == Approx( sqrt(2) ) );
    }

    SECTION( "normal length (2)" )
    {
	Vec2d<int> p2{-1,1};
	
	double len2{p2.length()};
	CHECK( len2 == Approx( sqrt(2) ) );
    }

    SECTION( "normal length (3)" )
    {

	Vec2d<int> p3{1,-1};
	
	double len3{p3.length()};
	CHECK( len3 == Approx( sqrt(2) ) );
    }

    SECTION( "normal length (4)" )
    {
	Vec2d<int> p4{-1,-1};
	
	double len4{p4.length()};
	CHECK( len4 == Approx( sqrt(2) ) );
    }

    SECTION( "edge cases length" )
    {	
	Vec2d<int> p1{0,0};
	
	CHECK( p1.length() == Approx(0) );
    }

    SECTION( "edge cases length" )
    {
	Vec2d<int> p2{1,0};

	CHECK( p2.length() == Approx(1) );
    }

    SECTION( "edge cases length" )
    {
	Vec2d<int> p3{0,1};

	CHECK( p3.length() == Approx(1) );
    }
}

TEST_CASE( "Vec2d comparison test", "[Vec2d]")
{
    SECTION( "{1,1} & {1,1}" )
    {
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};

	CHECK( p1 == p2 );
	CHECK_FALSE( p1 != p2 );
    }
    
    SECTION( "{0,0} & {1,1}" )
    {
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{0,0};
	
   	CHECK_FALSE( p1 == p2 );
	CHECK( p1 != p2 );	
    }
    
    SECTION( "{1,1} & {1, 1 + DEFAULT_PREC}" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{1, 1 + DEFAULT_PREC};
   
	CHECK( p1 == p2 );
	CHECK_FALSE( p1 != p2 );	
    }

    SECTION( "{1,1} == {1 + DEFAULT_PREC, 1}" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{1 + DEFAULT_PREC, 1};
   
	CHECK( p1 == p2 );
	CHECK_FALSE( p1 != p2 );
    }

    SECTION( "{1,1} == {1, 1 + (2 * DEFAULT_PREC)}" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{1, 1 + (2 * DEFAULT_PREC)};
   
	CHECK_FALSE( p1 == p2 );
	CHECK( p1 != p2 );
    }

    SECTION( "{1,1} == {1 + (2 * DEFAULT_PREC), 1}" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{1 + (2 * DEFAULT_PREC), 1};
   
	CHECK_FALSE( p1 == p2 );
	CHECK( p1 != p2 );
    }

    SECTION( "0 precision false" )
    {
	Vec2d<double> p1{1,1, 0.0};
	Vec2d<double> p2{1, 1 + DEFAULT_PREC, 0.0};
   
	CHECK_FALSE( p1 == p2 );
	CHECK( p1 != p2 );
    }

    SECTION( "0 precision true" )
    {
	Vec2d<double> p1{1,1, 0.0};
	Vec2d<double> p2{1, 1, 0.0};
   
	CHECK( p1 == p2 );
	CHECK_FALSE( p1 != p2 );
    }

    SECTION( "Different precision true" )
    {
	Vec2d<double> p1{1, 1, 0.0};
	Vec2d<double> p2{1, 1 + 2, 2};
   
	CHECK( p1 == p2 );
	CHECK_FALSE( p1 != p2 );
    }

    SECTION( "Different precision true" )
    {
	Vec2d<double> p1{1, 1, 0.0};
	Vec2d<double> p2{1, 1 + 2, 2};
   
	CHECK( p1 == p2 );
	CHECK_FALSE( p1 != p2 );
    }

    SECTION( "Different precision false" )
    {
	Vec2d<double> p1{1, 1, 3};
	Vec2d<double> p2{1, 1 + 2, 2};
   
	CHECK( p1 == p2 );
	CHECK_FALSE( p1 != p2 );
    }
}

TEST_CASE( "Vec2d scalar multiplication test", "[Vec2d]")
{
    SECTION( "p * x (1)" )
    {
	Vec2d<double> p1{1,1};

	CHECK( (p1 * 2.0) == Vec2d<double>{2,2} );
    }

    SECTION( "x * p (2)" )
    {	
	Vec2d<double> p1{1,1};

	CHECK( (3.14 * p1) == Vec2d<double>{3.14,3.14} );
    }

    SECTION( "0.0 * p" )
    {
	Vec2d<double> p1{1,1};

	CHECK( (p1 * 0.0) == Vec2d<double>{0,0} );
    }

    SECTION( "p *= x" )
    {	
	Vec2d<double> p1{1,1};

	CHECK( (p1 *= -1) == Vec2d<double>{-1, -1} );
    }
}

TEST_CASE( "Vec2d scalar divison test", "[Vec2d]")
{
    SECTION( "p / x" )
    {
	Vec2d<double> p1{1,1};

	CHECK( (p1 / 2.0) == Vec2d<double>{0.5, 0.5} );
	CHECK( (p1 / 0.5) == Vec2d<double>{2, 2} );
    }
}

TEST_CASE( "Vec2d cross product test", "[Vec2d]")
{
    SECTION( "cross( p1, p2 ) == 0" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{p1};
	
	CHECK( cross(p1, p2) == 0 );

    }

    SECTION( "cross( p1, p2 ) (1)" )
    {
	Vec2d<double> p3{10.10,10.10};
	Vec2d<double> p4{p3};
	
	CHECK( cross(p3, p4) == 0 );
    }
   
    SECTION( "cross( p1, p2 ) (2)" )
    {
	Vec2d<double> p1{0,1};
	Vec2d<double> p2{1,0};
	
	CHECK( cross(p1, p2) == -1 );
    }

    SECTION( "cross( p1, p2 ) (3)" )
    {	
	Vec2d<double> p1{10.5, 1.56};
	Vec2d<double> p2{-13.8, 34.2};
	
	CHECK( cross(p1, p2) == Approx( (10.5 * 34.2) - (1.56*-13.8) ) );
    }    
    
    SECTION( "cross( p1, p2 ) (4)" )
    {
	Vec2d<int> p1{1, 0};
	Vec2d<int> p2{-4, 3};

	int res = dalg::cross(p1, p2);
	CHECK( res == 3 );
    }

    SECTION( "cross( p1, p2 ) (5)" )
    {
	Vec2d<int> p1{1, 3};
	Vec2d<int> p2{2, 4};

	int res = dalg::cross(p1, p2);
	CHECK( res == -2 );
    }

    SECTION( "cross( p1, p2 ) (6)" )
    {
	Vec2d<int> p1{2, -1};
	Vec2d<int> p2{1, 3};

	int res = dalg::cross(p1, p2);
	CHECK( res == 7 );
    }
}

TEST_CASE( "Vec2d dot product test", "[Vec2d]")
{
    SECTION( "dot( p1, p2 ) (1)" )
    {
	Vec2d<double> p1{1,1};
	Vec2d<double> p2{p1};
	
	CHECK( dot(p1, p2) == 2 );
    }

    SECTION( "dot( p1 ,p2 ) (2)" )
    {
    	Vec2d<double> p3{10.10,10.10};
	Vec2d<double> p4{p3};
	
	CHECK( dot(p3, p4) == Approx( (10.10 * 10.10) + (10.10 * 10.10) ) );
    }

    SECTION( "dot( p1, p2 ) (3)" )
    {
    	Vec2d<double> p3{1,0};
	Vec2d<double> p4{0,1};
	
	CHECK( dot(p3, p4) == 0 );
    }

    SECTION( "dot( p1, p2 ) (4)" )
    {
    	Vec2d<double> p3{0,1};
	Vec2d<double> p4{1,0};
	
	CHECK( dot(p3, p4) == 0 );
    }

    SECTION( "dot( p1, p2 ) (5)" )
    {
    	Vec2d<double> p3{0,0};
	Vec2d<double> p4{0,0};
	
	CHECK( dot(p3, p4) == 0 );
    }

    SECTION( "dot( p1, p2 ) (6)" )
    {
	Vec2d<int> p1{2,4};
	Vec2d<int> p2{4,2};

	CHECK( dalg::dot(p1, p2) == 16 );
    }
}

TEST_CASE( "Vec2d projection test", "[Vec2d]")
{
    SECTION( "project( p1, p2 ) (1)" )
    {
	Vec2d<double> p1{2, 3};
	Vec2d<double> p2{1, 2};

	Vec2d<double> tmp = dalg::project(p1, p2);
	CHECK( tmp == Vec2d<double>(8.0/5.0, 16.0/5.0) );
    }
    
    SECTION( "project( p1, p2 ) (2)" )
    {
	Vec2d<double> p1{0, -2};
	Vec2d<double> p2{1, 3};

	Vec2d<double> tmp = dalg::project(p1, p2);
	CHECK( tmp == Vec2d<double>(-3.0/5.0, -9.0/5.0) );
    }

    SECTION( "project( p1, p2 ) (3)" )
    {
	Vec2d<double> p1{1, 1};
	Vec2d<double> p2{1, 1};

	Vec2d<double> tmp = dalg::project(p1, p2);
	CHECK( tmp == Vec2d<double>(1, 1) );
    }

    SECTION( "project( p1, p2 ) (4)" )
    {
	Vec2d<int> p1{0, -2};
	Vec2d<int> p2{1, 3};

	Vec2d<double> tmp = dalg::project<int, double>(p1, p2);
	tmp.prec = 0.1; //Set precision quite high since get precision error
	
	CHECK( tmp == Vec2d<double>(-3.0/5.0, -9.0/5.0) );
    }
}

TEST_CASE( "Vec2d angle test", "[Vec2d]")
{
    SECTION( "p.angle(p)" )
    {
	Vec2d<double> p1{1, 1};

	CHECK( angle(p1,p1) < 0.01 );
	CHECK( rad_angle(p1,p1) < 0.01 );
    }

    SECTION( "90 degree" )
    {
	Vec2d<double> p1{0, 1};
	Vec2d<double> p2{1, 0};

	CHECK( Approx(90) == angle(p1,p2) );
	CHECK( Approx(PI / 2) == rad_angle(p1,p2) );
    }

    SECTION( "45 degree" )
    {
	Vec2d<double> p1{1, 1};
	Vec2d<double> p2{1, 0};

	CHECK( Approx(45) == angle(p1,p2) );
	CHECK( Approx(PI / 4) == rad_angle(p1,p2) );
    }
}
