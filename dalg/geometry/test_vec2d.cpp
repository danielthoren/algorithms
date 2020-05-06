#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "vec2d.h"

#define DEBUG 1

using namespace dalg;

//------------- Test constructor ------------- 
bool constructor_test()
{
    bool res{true};
    {
	bool result{true};
    
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};

	result &= (p2.x == p1.x && p2.y == p1.y);
	result &= (p2 == p1);

	p1.x = 10;

	result &= (p1.x == 10 && p2.x == 1);

	if (DEBUG && !result)
	    std::cout << "Test 1 failed" << std::endl;	

	res = res & result;
    }
    return res;
}


bool arithmetic_test()
{
    bool global_result{true};
    
    //------------- Test Addition -------------
    {
	bool result = true;
	
	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
    
	Vec2d<int> p3{p1 + p2};

	result &= (p3.x == p1.x + p2.x &&
		   p3.y == p1.y + p2.y);

	p1 += p2;

	result &= (p1.x == 2 &&
		   p1.y == 2);

	if (DEBUG && !result)
	    std::cout << "Addition test failed" << std::endl;

	global_result &= result;
    }

    //------------- Test substraction -------------
    {

	bool result = true;

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{10, 10};
	
	Vec2d<int> p4{p1 - p2};

	result &= (p4.x == p1.x - p2.x &&
		  p4.y == p1.y - p2.y);

	p2 -= p1;

	result &= (p2.x == 9 &&
		   p2.y == 9);

	if (DEBUG && !result)
	    std::cout << "Substraction test failed" << std::endl;    

	global_result = global_result && result;
    }
    return global_result;
}

bool length_test()
{
    bool global_result{true};
    //------------- Test Length -------------
    {
	bool result = true;
    
	Vec2d<int> p1{1,1};    
	double len{ p1.length() };
    
	result &= ( len == sqrt(2) );

	Vec2d<int> p2{p1};  
    
	Vec2d<int> p3 = p1 - p2;
	result = (p3.length() == 0);

	if (DEBUG && !result)
	    std::cout << "Length test failed" << std::endl;

	global_result &= result;
    }
    
    return global_result;
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

bool dot_test()
{
    bool global_result{true};
    //------------- Test dot (*) product -------------
    {
	bool result = true;

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};
    
	result &= dalg::dot(p1, p2) == 2;

	if (DEBUG && !result)
	    std::cout << "Dot product test 1 falied" << std::endl;    

	global_result &= result;
    }

    {
	bool result = true;

	Vec2d<int> p1{2,4};
	Vec2d<int> p2{4,2};

	result &= dalg::dot(p1, p2) == 16;

	if (DEBUG && !result)
	    std::cout << "Dot product test 2 falied" << std::endl;    

	global_result &= result;
    }
    
    return global_result;
}


bool cross_test()
{
    bool global_result{true};
    //------------- Test Determinant -------------
    {
	bool result = true;

	Vec2d<int> p1{1,1};
	Vec2d<int> p2{p1};

	int res = dalg::cross(p1, p2);	
	result &= res == 0;

	if (DEBUG && !result)
	    std::cout << "Cross test 1 falied" << std::endl;

	global_result &= result;
    }

    {
	bool result = true;

	Vec2d<int> p1{1, 0};
	Vec2d<int> p2{-4, 3};

	int res = dalg::cross(p1, p2);
	result &= res == 3;

	if (DEBUG && !result)
	    std::cout << "Cross test 2 falied" << std::endl;

	global_result &= result;
    }
    
    {
	bool result = true;

	Vec2d<int> p1{1, 3};
	Vec2d<int> p2{2, 4};

	int res = dalg::cross(p1, p2);
	result &= res == -2;

	if (DEBUG &&!result)
	    std::cout << "Cross test 3 falied" << std::endl;

	global_result &= result;
    }

    {
	bool result = true;

	Vec2d<int> p1{2, -1};
	Vec2d<int> p2{1, 3};

	int res = dalg::cross(p1, p2);
	result &= res == 7;

	if (DEBUG && !result)
	    std::cout << "Cross test 4 falied" << std::endl;

	global_result &= result;
    }

    return global_result;
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

bool scalar_test()
{
    bool global_result{true};

    {
	bool result = true;

	Vec2d<double> p1{1, 1};

	p1 = p1 * 2.0;

	result &= p1.x == 2.0 && p1.x == 2.0;
	
	if (DEBUG && !result)
	    std::cout << "scalar test 1 falied" << std::endl;

	global_result &= result;
    }

    return global_result;    
}


int main()
{

    if (!constructor_test())
    {
	std::cout << "Constructor test failed" << std::endl;
    }
    if (!arithmetic_test())
    {
	std::cout << "Arithmetic test failed" << std::endl;
    }
    if (!length_test())
    {
	std::cout << "length test failed" << std::endl;
    }
    if (!comparison_test())
    {
	std::cout << "comparison test failed" << std::endl;
    }
    if (!dot_test())
    {
	std::cout << "dot test failed" << std::endl;
    }
    if (!cross_test())
    {
	std::cout << "cross test failed" << std::endl;
    }
    if (!project_test())
    {
	std::cout << "project test failed" << std::endl;
    }
    if (!scalar_test())
    {
	std::cout << "scalar test failed" << std::endl;
    }
    

    return 0;
}
