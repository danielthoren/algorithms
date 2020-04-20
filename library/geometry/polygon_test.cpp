#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "point.h"
#include "Line.h"
#include "Polygon.h"

using namespace std;

bool constructor()
{
    point<int> p1(0, 0);
    point<int> p2(1, 1);
    point<int> p3(1, -1);
    std::vector<point<int>> pts{p1, p2, p3};

    Polygon poly(pts);

    std::vector<LineSegment<int>>& segments = poly.get_segments();

    if (!(segments[0].get_start_point() == p1 &&
	segments[0].get_end_point() == p2 &&
	segments[1].get_start_point() == p2 &&
	segments[1].get_end_point() == p3 &&
	segments[2].get_start_point() == p3 &&
	  segments[2].get_end_point() == p1))
    {
	cout << "Error when constructing polygon" << endl;
	return false;
    }

    point<int> p4(4,0);

    poly.add_point(p4, 1);

    if (!(segments[0].get_start_point() == p1 &&
	  segments[0].get_end_point() == p2 &&
	  segments[1].get_start_point() == p2 &&
	  segments[1].get_end_point() == p4 &&
	  segments[2].get_start_point() == p4 &&
	  segments[2].get_end_point() == p3 &&
	  segments[3].get_start_point() == p3 &&
	  segments[3].get_end_point() == p1))
    {
	cout << "Point not inserted correctly in polygon" << endl;
	return false;
    }
    return true;
}

bool area()
{
    {
	point<int> p1(0, 0);
	point<int> p2(1, 1);	
	point<int> p3(4, 0);
	point<int> p4(1, -1);
	std::vector<point<int>> pts{p1, p2, p3, p4};

	Polygon poly(pts);
    
	if (4 - poly.polygon_area<long double>() > 0.01)
	{
	    cout << "Failed first area test polygon!" << endl;
	    return false;
	}
    }

    {
	point<int> p1(0, 0);
	point<int> p2(10, 0);
	point<int> p3(0, 10);
	
	std::vector<point<int>> pts{p1, p2, p3};

	Polygon poly(pts);

	if (50 - poly.polygon_area<long double>() > 0.01)
	{
	    cout << "Failed second area test polygon!" << endl;
	    return false;
	}	
    }

    {
	point<int> p1(41, -6);
	point<int> p2(-24, -74);
	point<int> p3(-51, -6);
	point<int> p4(73, 17);
	point<int> p5(-30, -34);
	
	std::vector<point<int>> pts{p1, p2, p3, p4, p5};

	Polygon poly(pts);

	if (3817.5 - poly.polygon_area<long double>() > 0.01)
	{
	    cout << "Failed third area test polygon!" << endl;
	    return false;
	}	
    }
    
    return true;
	
}

int main()
{
    if (!constructor())
    {
	cout << "Constructor test failed!" << endl << endl;
	return -1;
    }
    if (!area())
    {
	cout << "Area test failed!" << endl << endl;
    }
    

    return 0;
}
