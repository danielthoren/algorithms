#include "vec2d.h"
#include "line_segment.h"
#include <cstdio>
#include <variant>

#include <iostream>

using namespace std;

dalg::LineSegment<double> read_line()
{
    double x1, y1, x2, y2;
    scanf(" %lf", &x1);
    scanf(" %lf", &y1);
    scanf(" %lf", &x2);
    scanf(" %lf", &y2);
    
    dalg::LineSegment<double> l1{x1, y1, x2, y2};

    return l1;
}

int main()
{
    int cases{};
    
    scanf(" %d", &cases);

    for (int i{0}; i < cases; i++)
    {	
    	dalg::LineSegment<double> l1 = read_line();
    	dalg::LineSegment<double> l2 = read_line();

	auto res = l1.intersection(l2);
	if (std::holds_alternative<std::monostate>(res))
	{
	    auto res = l1.closest_points(l2);
	    printf("%.2lf\n", std::get<0>(res).distance(std::get<1>(res)));
	}
	else
	{
	    printf("0.00\n");
	}
    }
}
