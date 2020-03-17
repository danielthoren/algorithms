#include "point.h"
#include "LineSegment.h"
#include <cstdio>
#include <variant>

#include <iostream>

using namespace std;

LineSegment<long double> read_line()
{
    long double x1, y1, x2, y2;
    scanf(" %Lf", &x1);
    scanf(" %Lf", &y1);
    scanf(" %Lf", &x2);
    scanf(" %Lf", &y2);
    
    LineSegment<long double> l1{x1, y1, x2, y2};

    return l1;
}

int main()
{
    // int cases{};
    
    // scanf(" %d", &cases);

    // for (int i{0}; i < cases; i++)
    // {	
    // 	LineSegment<long double> l1 = read_line();
    // 	LineSegment<long double> l2 = read_line();

    // }

    LineSegment<double> line(0, 0, 3, 2);
    point<double> x(-6, 4);
    
    point<double> res = line.closest_point(x);

    std::cout << res << std::endl;
}
