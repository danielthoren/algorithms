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

    //--------------------Test Vec2d constructor---------------------------
    {
	bool result{true};

	Vec2d<int> c1(0,0);
	Vec2d<int> c2(0,1);
	Vec2d<int> c3(1,1);
	Vec2d<int> c4(0,1);

	Rectangle<int> r1(c1, c2, c3, c4);

	std::vector<Vec2d<int>>& c = r1.get_corners();
	result &= c[0] == c1 && c[1] == c2 && c[2] == c3 && c[3] == c4;

	if (DEBUG && !result)
	    std::cout << "constructor Test 1 failed" << std::endl;	

	res = res & result;
    }

    //--------------------Test LineSegment constructor---------------------------
    {
	bool result{true};

	Vec2d<int> c1(0,0);
	Vec2d<int> c2(0,1);
	Vec2d<int> c3(1,1);
	Vec2d<int> c4(0,1);

	LineSegment<int> l1(c1, c2);
	LineSegment<int> l2(c3, c4);	

	Rectangle<int> r1(l1, l2);

	std::vector<Vec2d<int>>& c = r1.get_corners();
	result &= c[0] == c1 && c[1] == c2 && c[2] == c3 && c[3] == c4;	   

	if (DEBUG && !result)
	    std::cout << "constructor Test 2 failed" << std::endl;	

	res = res & result;
    }

    //--------------------Test copy constructor---------------------------
    {
	bool result{true};

	Vec2d<int> c1(0,0);
	Vec2d<int> c2(0,1);
	Vec2d<int> c3(1,1);
	Vec2d<int> c4(0,1);

	Rectangle<int> r(c1, c2, c3, c4);	

	Rectangle<int> r1(r);	

	std::vector<Vec2d<int>>& c = r1.get_corners();
	result &= c[0] == c1 && c[1] == c2 && c[2] == c3 && c[3] == c4;

	if (DEBUG && !result)
	    std::cout << "constructor Test 3 failed" << std::endl;	

	res = res & result;
    }    
    
    return res;
}


bool min_max_test()
{
    bool res{true};

    //--------------------Test Vec2d constructor---------------------------
    {
	bool result{true};

	Vec2d<int> c1(0,1);
	Vec2d<int> c2(1,0);
	Vec2d<int> c3(1,2);
	Vec2d<int> c4(2,1);

	Rectangle<int> r1(c1, c2, c3, c4);

	std::pair<Vec2d<double>, Vec2d<double>> ret = r1.get_min_max_projection<double>( Vec2d<int>(1,0) );
	ret.first.prec = 0.1;
	ret.second.prec = 0.1;

	result &= ret.first == Vec2d<double>(0,0) && ret.second == Vec2d<double>(2,0);

	if (DEBUG && !result)
	    std::cout << "min_max Test 1 failed" << std::endl;	

	res = res & result;
    }

    return res;
}


int main()
{

    if (!constructor_test())
    {
	std::cout << "Constructor test failed" << std::endl;
    }
    if (!min_max_test())
    {
	std::cout << "min_max test failed" << std::endl;
    }    

    return 0;
}
