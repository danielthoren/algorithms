#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <variant>

#define DEBUG 1

#include "../vec2d.h"
#include "../circle.h"

using namespace dalg;

bool test_circle_circle()
{
    bool res{true};
    //--------------------Test random ---------------------------
    {
	bool result = true;

	Circle<double> c1{Vec2d<double>{0,0}, 5};
	Circle<double> c2{Vec2d<double>{5,0}, 5};

        auto col = c1.collision(c2);

	if (!col)
	{
	    result = false;
	}
	else
	{
	    Collision<double>& col_act = col.value();

	    Contact<double> c0{Vec2d<double>{0,0},
			       Vec2d<double>{-1,0},
			       5};

	    Collision<double> col_c;
	    
	    col_c.contacts.push_back(c0);
	    col_c.contact_count = 1;
	    col_c.A = &c1;
	    col_c.B = &c2;

	    result &= col_act == col_c;
	}
	

	if (DEBUG && !result)
	    std::cout << "circle_circle test 1 falied" << std::endl;

	res &= result;
    }

    return res;
}


int main()
{
    if (!test_circle_circle())
    {
	std::cout << "--------------------circle_circle test failed------------------------" << std::endl;
	return -1;
    }
    return 0;
}
