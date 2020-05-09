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

bool center_point_test()
{   
    bool res{true};

    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> ret = r1.get_center_point();
	ret.prec = 0.01;

	result &= ret == Vec2d<double>(0.5, 0.5);

	if (DEBUG && !result)
	    std::cout << "min_max Test 1 failed" << std::endl;	

	res = res & result;
    }
    return res;
}

bool collision_x_test()
{
    bool res{true};

    int test_count{1};

    //--------------------Test same angle overlap x-axis---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0.5,1);
	Vec2d<double> a2(2  ,1);
	Vec2d<double> a3(2  ,0);
	Vec2d<double> a4(0.5,0);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "X collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }

    //--------------------Test same angle x-axis, only collision in line segment---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1,1);
	Vec2d<double> a2(2,1);
	Vec2d<double> a3(2,0);
	Vec2d<double> a4(0,1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "X collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }


    //--------------------Test same angle x-axis, no collision---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(10,0);
	Vec2d<double> a2(11,0);
	Vec2d<double> a3(11,1);
	Vec2d<double> a4(10,1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= !r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "X collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }    


    //--------------------Test different angle x-axis, deep collision---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0.75,2);
	Vec2d<double> a2(2   ,2);
	Vec2d<double> a3(2   ,0);
	Vec2d<double> a4(0.75,0);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "X collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }


    //--------------------Test different angle x-axis, only collision in point---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1,1);
	Vec2d<double> a2(2,2);
	Vec2d<double> a3(2,0);
	Vec2d<double> a4(0,1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "X collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }

    //--------------------Test different angle x-axis, no collision far---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(10,10);
	Vec2d<double> a2(11,11);
	Vec2d<double> a3(11,0);
	Vec2d<double> a4(0,11);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= !r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "X collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }


    //--------------------Test different angle x-axis, no collision close---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0.5,  1);
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1.1,1);
	Vec2d<double> a2(1.1,0);
	Vec2d<double> a3(2  ,0);
	Vec2d<double> a4(2  ,1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= !r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "X collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }
    
    return res;
}


bool collision_y_test()
{
    bool res{true};

    int test_count{1};

    //--------------------Test same angle overlap y-axis---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0, 0.5);
	Vec2d<double> a2(1, 0.5);
	Vec2d<double> a3(1, 2  );
	Vec2d<double> a4(0, 2 );

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "Y collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }

    //--------------------Test same angle y-axis, only collision in line segment---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,1);
	Vec2d<double> a2(1,1);
	Vec2d<double> a3(1,2);
	Vec2d<double> a4(0,2);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "Y collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }


    //--------------------Test same angle y-axis, no collision---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,10);
	Vec2d<double> a2(1,10);
	Vec2d<double> a3(1,11);
	Vec2d<double> a4(0,11);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= !r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "Y collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }    


    //--------------------Test different angle y-axis, deep collision---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0, 0.75);
	Vec2d<double> a2(1, 0.75);
	Vec2d<double> a3(0, 2);
	Vec2d<double> a4(1, 2);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "Y collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }


    //--------------------Test different angle y-axis, only collision in point---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0.5, 1 );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,1);
	Vec2d<double> a2(1,1);
	Vec2d<double> a3(1,2);
	Vec2d<double> a4(0,2);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "Y collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }

    //--------------------Test different angle y-axis, no collision far---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0.5,1  );
	Vec2d<double> c2(1  ,0.5);
	Vec2d<double> c3(0.5,  0);
	Vec2d<double> c4(0  ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,10);
	Vec2d<double> a2(1,10);
	Vec2d<double> a3(1,20);
	Vec2d<double> a4(0,20);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= !r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "Y collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }


    //--------------------Test different angle y-axis, no collision close---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0.5,1 );
	Vec2d<double> c2(1 ,0.5);
	Vec2d<double> c3(0.5, 0);
	Vec2d<double> c4(0 ,0.5);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0,1.1);
	Vec2d<double> a2(1,1.1);
	Vec2d<double> a3(1,2  );
	Vec2d<double> a4(0,2  );

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= !r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "Y collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }
    
    return res;
}

bool collision_test()
{
    bool res{true};
    
    res &= collision_x_test();
    res &= collision_y_test();

    int test_count{1};

    //--------------------Test both axis, deep collision---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(0.75,0.75);
	Vec2d<double> a2(0.75,2   );
	Vec2d<double> a3(2,2      );
	Vec2d<double> a4(2,0.75   );

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "XY collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }

    //--------------------Test both axis, point collision---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0,0);
	Vec2d<double> c2(1,0);
	Vec2d<double> c3(1,1);
	Vec2d<double> c4(0,1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1,1);
	Vec2d<double> a2(1,2);
	Vec2d<double> a3(2,2);
	Vec2d<double> a4(2,1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "XY collision Test " << test_count << " failed" << std::endl;

	++test_count;

	res = res & result;
    }

    //--------------------Test both axis, almost collision---------------------------    
    {
	bool result{true};

	Vec2d<double> c1(0, 0);
	Vec2d<double> c2(1, 0);
	Vec2d<double> c3(1, 1);
	Vec2d<double> c4(0, 1);

	Rectangle<double> r1(c1, c2, c3, c4);

	Vec2d<double> a1(1.1, 1.1);
	Vec2d<double> a2(1.1, 2  );
	Vec2d<double> a3(2  , 2  );
	Vec2d<double> a4(2  , 1.1);

	Rectangle<double> r2(a1, a2, a3, a4);
       
	result &= !r1.collision(r2);

	if (DEBUG && !result)
	    std::cout << "XY collision Test " << test_count << " failed" << std::endl;

	++test_count;

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
    if (!center_point_test())
    {
	std::cout << "center_point test failed" << std::endl;
    }
    if (!collision_test())
    {
	std::cout << "collision test failed" << std::endl;
    }    
    
    return 0;
}
