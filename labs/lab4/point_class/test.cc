#include <cassert>
#include <string>
#include <algorithm>
#include <cmath>

#include "point.h"

using namespace std;

int main()
{
    Point_2d<int> p1{1,1};
    Point_2d<int> p2{p1};

    assert(p2.x_cord == p1.x_cord && p2.y_cord == p1.y_cord);
    assert(p2 == p1);

    Point_2d<int> p3{p1 + p2};

    assert(p3.x_cord == p1.x_cord + p2.x_cord &&
	   p3.y_cord == p1.y_cord + p2.y_cord);

    double len{p2.length()};
    assert(len == sqrt(2));

    p3 = p1 - p2;

    double len2 = p3.length();
    assert(len2 == 0);
    assert(p3 != p2);
    assert(p3 < p2);
    assert(p2 > p3);
    assert(!(p2 < p3));
    assert(!(p3 > p2));

    assert(p2 <= p1);
    assert(p2 >= p1);

    assert(p1.scalar(p2) == 2);

    assert(p1.determinant(p2) == 0);
    
    
}
