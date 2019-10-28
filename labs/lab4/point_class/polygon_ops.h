#include "point.h"

#include <vector>
#include <cmath>

#include <iostream>

#ifndef POLYGON_OPS
#define POLYGON_OPS

template <typename T>
long double polygon_area(std::vector<Point_2d<T>>& pts);

/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/

template <typename T>
long double polygon_area(std::vector<Point_2d<T>>& pts)
{
    long double area{0};
    for (long unsigned int p{0}; p < pts.size(); p++)
    {
	area += pts.at(p).determinant(pts.at( (p + 1)%pts.size() ));
	// area += (pts[prev].x + pts[p].x) * (pts[prev].y - pts[p].y);
	// prev = p;
    }
    //std::cout << area << " abs: " << std::abs(area) << std::endl;
    return area/2;
}

#endif
