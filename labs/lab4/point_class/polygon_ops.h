#include "point.h"

#include <vector>

#ifndef POLYGON_OPS
#define POLYGON_OPS

template <typename T>
double polygon_area(std::vector<Point_2d<T>>& pts);

template <typename T>
bool polygon_clockwise(std::vector<Point_2d<T>>& pts);

#include "polygon_ops.tcc"

#endif
