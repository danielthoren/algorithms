#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "rectangle.h"
#include "vec2d.h"
#include "line_segment.h"

#define DEBUG 1

using namespace dalg;

bool constructor_test()
{
    bool res{true};

    //--------------------Test copy constructor---------------------------
    {

	bool result{true};

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};

	result &= (p2.x == p1.x && p2.y == p1.y);
	result &= (p2 == p1);

	if (DEBUG && !result)
	    std::cout << "Constructor test 1 failed" << std::endl;

	res &= result;
	
    }
    
    return res;
}

bool test_addition()
{
    bool res{true};

    //--------------------Test Vec2d + Vec2d ---------------------------
    {
	bool result = true;

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
	
	Vec2d<int> p3{p1 + p2};

	result &= (p3.x == p1.x + p2.x &&
		  p3.y == p1.y + p2.y);

	if (DEBUG && !result)
	    std::cout << "Addition test 1 failed" << std::endl;

	res &= result;
    }

    //--------------------Test Vec2d += Vec2d ---------------------------
    {
	bool result = true;

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
	
	p2 += p1;

	result &= (p2.x == 2 && p2.y == 2);
	result &= (p1.x == 1 && p1.y == 1);

	if (DEBUG && !result)
	    std::cout << "Addition test 2 failed" << std::endl;

	res &= result;
    }

    return res;
}

bool test_substraction()
{
    bool res{true};

    //--------------------Test Vec2d - Vec2d ---------------------------
    {
	bool result = true;

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
	
	Vec2d<int> p3{p1 - p2};

	result &= (p3.x == p1.x + p2.x &&
		  p3.y == p1.y + p2.y);

	if (DEBUG && !result)
	    std::cout << "Substraction test 1 failed" << std::endl;

	res &= result;
    }

    //--------------------Test Vec2d -= Vec2d ---------------------------
    {
	bool result = true;

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
	
	p2 -= p1;

	result &= (p2.x == 2 && p2.y == 2);
	result &= (p1.x == 1 && p1.y == 1);

	if (DEBUG && !result)
	    std::cout << "Substraction test 2 failed" << std::endl;

	res &= result;
    }

    return res;
}


bool length_test()
{
    bool res{true};

    //--------------------Test normal length ---------------------------
    {
	bool result = true;
	
	Vec2d<int> p1{1,1};
	
	double len{p1.length()};
	result &= (len == sqrt(2));

	Vec2d<int> p2{-1,1};
	
	double len2{p2.length()};
	result &= (len2 == sqrt(2));

	Vec2d<int> p3{1,-1};
	
	double len3{p3.length()};
	result &= (len3 == sqrt(2));

	Vec2d<int> p4{-1,-1};
	
	double len4{p4.length()};
	result &= (len4 == sqrt(2));

	if (DEBUG && !result)
	    std::cout << "Length test 1 failed" << std::endl;
	
	res &= result;
    }

    //--------------------Test edge cases length ---------------------------
    {    
	Vec2d<int> p1{0,0};
	
	result &= (p1.length() == 0);

	Vec2d<int> p2{1,0};

	result &= (p2.length() == 1);

	Vec2d<int> p3{0,1};

	result &= (p3.length() == 1);	

	if (DEBUG && !result)
	    std::cout << "Length test 2 failed" << std::endl;
	
	res &= result;
    }

    return res;
}

bool comparison_test()
{
    bool global_result{true};    
    //------------- Test comparison operators -------------
    {
	bool result = true;

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};

	Vec2d<int> p3{p1 - p2};
   
	result &= (p3 != p2);
	result &= (p1 == p2);

	if (DEBUG && !result)
	    std::cout << "Compairson test 1 failed" << std::endl;

	global_result &= result;
    }
    return global_result;
}

bool scalar_mult_test()
{
    bool res{true};

    //--------------------Test normal scalar ---------------------------
    {
	bool result = true;
	
	Vec2d<double> p1{1,1};

	result &= (p1 * 2) == Vec2d<double>{2,2};

	if (DEBUG && !result)
	    std::cout << "Scalar product test 1 falied" << std::endl;    
	
	res &= result;
    }

    {
	bool result = true;
	
	Vec2d<double> p1{1,1};

	result &= (p1 * 3.14) == Vec2d<double>{3.14,3.14};

	if (DEBUG && !result)
	    std::cout << "Scalar product test 1 falied" << std::endl;    
	
	res &= result;
    }

    {
	bool result = true;
	
	Vec2d<double> p1{1,1};

	result &= (p1 * 0) == Vec2d<double>{0,0};

	if (DEBUG && !result)
	    std::cout << "Scalar product test 1 falied" << std::endl;    
	
	res &= result;
    }

    return res;
}

bool scalar_div_test()
{
    bool res{true};

    //--------------------Test normal scalar ---------------------------
    {
	bool result = true;
	
	Vec2d<double> p1{1,1};

	result &= (p1 / 2) == Vec2d<double>{0.5, 0.5};
	result &= (p1 / 0.5) == Vec2d<double>{2, 2};

	if (DEBUG && !result)
	    std::cout << "Scalar product test 1 falied" << std::endl;    
	
	res &= result;
    }

    return res;
}

bool cross_test()
{
    bool res{true};

    //--------------------Test cross( p,p ) == 0 ---------------------------
    {
	bool result = true;

	Vec2d<double> p1{1,1};
	Vec2d<double> p2{p1};
	
	result &= (cross(p1, p2) == 0);

	Vec2d<double> p3{10.10,10.10};
	Vec2d<double> p4{p3};
	
	result &= (cross(p3, p4) == 0);

	if (DEBUG && !result)
	    cout << "Cross test 1 falied" << endl;
	
	res &= result;
    }

    
    //--------------------Test normal cross ---------------------------
    {
	bool result = true;

	Vec2d<double> p1{0,1};
	Vec2d<double> p2{1,0};
	
	result &= (cross(p1, p2) == 1);

	Vec2d<double> p1{10.5, 1.56};
	Vec2d<double> p2{-13.8, 34.2};
	
	result &= (cross(p1, p2) == (10.5 * 34.2) - (1.56*-13.8));	

	if (DEBUG && !result)
	    cout << "cross test 2 falied" << endl;
	
	res &= result;
    }

        {
	bool result = true;

	Vec2d<int> p1{1, 0};
	Vec2d<int> p2{-4, 3};

	int res = dalg::cross(p1, p2);
	result &= res == 3;

	if (DEBUG && !result)
	    std::cout << "Cross test 3 falied" << std::endl;

	res &= result;
    }
    
    {
	bool result = true;

	Vec2d<int> p1{1, 3};
	Vec2d<int> p2{2, 4};

	int res = dalg::cross(p1, p2);
	result &= res == -2;

	if (DEBUG &&!result)
	    std::cout << "Cross test 4 falied" << std::endl;

	res &= result;
    }

    {
	bool result = true;

	Vec2d<int> p1{2, -1};
	Vec2d<int> p2{1, 3};

	int res = dalg::cross(p1, p2);
	result &= res == 7;

	if (DEBUG && !result)
	    std::cout << "Cross test 5 falied" << std::endl;

	res &= result;
    }

    return res;
}

bool dot_test()
{
    bool res{true};

    //--------------------Test normal dot ---------------------------
    {
	bool result = true;

	Vec2d<double> p1{1,1};
	Vec2d<double> p2{p1};
	
	result &= (dot(p1, p2) == 2);

	if (DEBUG && !result)
	    cout << "dot test 1 falied" << endl;
	
	res &= result;
    }

    {
	bool result = true;

    	Vec2d<double> p3{10.10,10.10};
	Vec2d<double> p4{p3};
	
	result &= (dot(p3, p4) == (10.10 * 10.10) + (10.10 * 10.10) );

	if (DEBUG && !result)
	    cout << "dot test 2 falied" << endl;
	
	res &= result;
    }

    {
	bool result = true;

    	Vec2d<double> p3{1,0};
	Vec2d<double> p4{0,1};
	
	result &= (dot(p3, p4) == 1);

	if (DEBUG && !result)
	    cout << "dot test 3 falied" << endl;
	
	res &= result;
    }

    {
	bool result = true;

    	Vec2d<double> p3{0,1};
	Vec2d<double> p4{1,0};
	
	result &= (dot(p3, p4) == -1);

	if (DEBUG && !result)
	    cout << "dot test 4 falied" << endl;
	
	res &= result;
    }

    {
	bool result = true;

    	Vec2d<double> p3{0,0};
	Vec2d<double> p4{0,0};
	
	result &= (dot(p3, p4) == 0);

	if (DEBUG && !result)
	    cout << "dot test 5 falied" << endl;
	
	res &= result;
    }

    {
	bool result = true;

	Vec2d<int> p1{2,4};
	Vec2d<int> p2{4,2};

	result &= dalg::dot(p1, p2) == 16;

	if (DEBUG && !result)
	    std::cout << "dot test 6 falied" << std::endl;

	res &= result;
    }

    return res;
}

bool project_test()
{
    bool global_result{true};

    {
	bool result = true;

	Vec2d<double> p1{2, 3};
	Vec2d<double> p2{1, 2};

	Vec2d<double> res = dalg::project(p1, p2);
	result &= res == Vec2d<double>(8.0/5.0, 16.0/5.0);

	if (DEBUG && !result)
	    std::cout << "Project test 1 falied" << std::endl;

	global_result &= result;
    }

    {
	bool result = true;

	Vec2d<double> p1{0, -2};
	Vec2d<double> p2{1, 3};

	Vec2d<double> res = dalg::project(p1, p2);
	result &= res == Vec2d<double>(-3.0/5.0, -9.0/5.0);

	if (DEBUG && !result)
	    std::cout << "Project test 2 falied" << std::endl;

	global_result &= result;
    }

    {
	bool result = true;

	Vec2d<double> p1{1, 1};
	Vec2d<double> p2{1, 1};

	Vec2d<double> res = dalg::project(p1, p2);
	result &= res == Vec2d<double>(1, 1);

	if (DEBUG && !result)
	    std::cout << "Project test 3 falied" << std::endl;

	global_result &= result;
    }

    {
	bool result = true;

	Vec2d<int> p1{0, -2};
	Vec2d<int> p2{1, 3};

	Vec2d<double> res = dalg::project<int, double>(p1, p2);
	res.prec = 0.1; //Set precision quite high since get precision error
	result &= res == Vec2d<double>(-3.0/5.0, -9.0/5.0);

	if (DEBUG && !result)
	    std::cout << "Project test 4 falied" << std::endl;

	global_result &= result;
    }

    return global_result;
}


int main()
{

    if (!constructor_test())
    {
	std::cout << "--------------------Constructor test failed------------------------" << std::endl;
    }
    if (!addition_test())
    {
	std::cout << "--------------------Addition test failed---------------------------" << std::endl;
    }
    if (!substraction_test())
    {
	std::cout << "--------------------Substraction test failed-----------------------" << std::endl;
    }
    if (!length_test())
    {
	std::cout << "--------------------length test failed-----------------------------" << std::endl;
    }
    if (!comparison_test())
    {
	std::cout << "--------------------comparison test failed-------------------------" << std::endl;
    }
    if (!scalar_mult_test())
    {
	std::cout << "--------------------scalar mult test failed------------------------" << std::endl;
    }
    if (!scalar_div_test())
    {
	std::cout << "--------------------scalar div test failed-------------------------" << std::endl;
    }
    if (!cross_test())
    {
	std::cout << "--------------------cross test failed------------------------------" << std::endl;
    }    
    if (!dot_test())
    {
	std::cout << "--------------------dot test failed------------------------------" << std::endl;
    }
    if (!project_test())
    {
	std::cout << "--------------------project test failed--------------------------" << std::endl;
    }    
    
    return 0;
}
