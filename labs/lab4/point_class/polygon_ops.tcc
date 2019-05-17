#include "polygon_ops.h"

template <typename T>
double polygon_area(std::vector<Point_2d<T>>& pts)
{
    pts.push_back(pts.at(0));

    double area{0};
    for (int p{0}; p < pts.size() - 1; p++)
    {
	area += pts.at(p).determinant(pts.at(p+1));	
    }
    return area/2;
}

template <typename T>
bool polygon_clockwise(std::vector<Point_2d<T>>& pts)
{
    T sum{0};
    for (int p{0}; p < pts.size() - 1; p++)
    {
	sum += (pts[p+1].x_cord - pts[p].y_cord)*(pts[p].y_cord + pts[p+1].y_cord);
    }

    return sum > 0;
}
