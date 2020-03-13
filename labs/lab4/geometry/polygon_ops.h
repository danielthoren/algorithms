#include "point.h"

#include <vector>
#include <cmath>

#include <iostream>

#ifndef POLYGON_OPS
#define POLYGON_OPS

/**
 * Author: Daniel Thorén
 *
 * Calculates the area of the given polygon. The polygon concists of a
 * number of points, two points beside each other in the vector are
 * assumed to be connected.
 *
 * Time complexity: O(n) n = points
 *
 * pts   : vector containing the points making up the polygon
 * return: The area of the polygon
 */
template <typename T>
long double polygon_area(std::vector<point<T>>& pts);

/*************************************************************/
/* Should be in tcc file, temporarily here for kattis        */
/*************************************************************/

template <typename T>
long double polygon_area(std::vector<point<T>>& pts)
{
    long double area{0};
    for (long unsigned int p{0}; p < pts.size(); p++)
    {
	area += pts.at(p).determinant(pts.at( (p + 1)%pts.size() ));
    }
    return area/2;
}

#endif
