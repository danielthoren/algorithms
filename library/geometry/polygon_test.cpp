#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "point.h"
#include "line.h"
#include "polygon.h"

using namespace std;

bool constructor()
{
    Point<int> p1(0, 0);
    Point<int> p2(1, 1);
    Point<int> p3(1, -1);
    std::vector<Point<int>> pts{p1, p2, p3};

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

    Point<int> p4(4,0);

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
	Point<int> p1(0, 0);
	Point<int> p2(1, 1);	
	Point<int> p3(4, 0);
	Point<int> p4(1, -1);
	std::vector<Point<int>> pts{p1, p2, p3, p4};

	Polygon poly(pts);
    
	if (4 - poly.polygon_area<long double>() > 0.01)
	{
	    cout << "Failed first area test polygon!" << endl;
	    return false;
	}
    }

    {
	Point<int> p1(0, 0);
	Point<int> p2(10, 0);
	Point<int> p3(0, 10);
	
	std::vector<Point<int>> pts{p1, p2, p3};

	Polygon poly(pts);

	if (50 - poly.polygon_area<long double>() > 0.01)
	{
	    cout << "Failed second area test polygon!" << endl;
	    return false;
	}	
    }

    {
	Point<int> p1(41, -6);
	Point<int> p2(-24, -74);
	Point<int> p3(-51, -6);
	Point<int> p4(73, 17);
	Point<int> p5(-30, -34);
	
	std::vector<Point<int>> pts{p1, p2, p3, p4, p5};

	Polygon poly(pts);

	if (3817.5 - poly.polygon_area<long double>() > 0.01)
	{
	    cout << "Failed third area test polygon!" << endl;
	    return false;
	}	
    }
    
    return true;	
}

bool min_distance()
{
    {
	Point<double> p1(0, 0);
	Point<double> p2(1, 1);	
	Point<double> p3(4, 0);
	Point<double> p4(1, -1);
	std::vector<Point<double>> pts{p1, p2, p3, p4};

	Polygon poly(pts);

	Point<double> pt1(0.5, 2);
	Point<double> pt2(1.5, 2);
	LineSegment<double> seg(pt1, pt2);

	auto res = poly.min_distance(seg);

	double dist = res.first.distance(res.second);

	if (1 - dist > 0.01)
	{
	    cout << "Failed min_distance 1" << endl;
	    return false;
	}
    }

    {
	Point<double> ip1(-5, -5);
	Point<double> ip2(5, -5);	
	Point<double> ip3(5, 5);
	Point<double> ip4(-5, 5);

	std::vector<Point<double>> ipts{ip1, ip2, ip3, ip4};
	Polygon inner(ipts);

	Point<double> op1(-10, -10);
	Point<double> op2(-10, 10);	
	Point<double> op3(10, 10);
	Point<double> op4(10, -10);

	std::vector<Point<double>> opts{op1, op2, op3, op4};
	Polygon outer(opts);

	auto res = inner.min_distance(outer);

	double dist = res.first.distance(res.second);

	if (2.5 - dist > 0.01)
	{
	    cout << "Failed min_distance 2" << endl;
	    return false;
	}
    }

    {
	Point<double> ip1(0,0);
	Point<double> ip2(1,0);	
	Point<double> ip3(1,1);

	std::vector<Point<double>> ipts{ip1, ip2, ip3};
	Polygon inner(ipts);

	Point<double> op1(3, -3);
	Point<double> op2(3, 3);	
	Point<double> op3(-4, 2);
	Point<double> op4(-1, -1);
	Point<double> op5(-2, -2);

	std::vector<Point<double>> opts{op1, op2, op3, op4, op5};
	Polygon outer(opts);

	auto res = inner.min_distance(outer);

	double dist = res.first.distance(res.second);

	if (0.70710678 - dist > 0.01)
	{
	    cout << "Failed min_distance 2" << endl;
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
    if (!min_distance())
    {
	cout << "min_distance test failed!" << endl << endl;
    }
    

    return 0;
}
