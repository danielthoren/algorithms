#include "point.h"
#include "line_segment.h"
#include <cstdio>
#include <variant>

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
	    printf("none\n");
	}
	else if (std::holds_alternative<dalg::Point<double>>(res))
	{
	    dalg::Point<double> pt = std::get<dalg::Point<double>>(res);
	    printf("%.2lf %.2lf\n", pt.x, pt.y);
	}
	else if (std::holds_alternative<dalg::LineSegment<double>>(res))
	{
	    dalg::LineSegment<double> lseg = std::get<dalg::LineSegment<double>>(res);
	    dalg::Point p1(lseg.p0);
	    dalg::Point p2(lseg.u + lseg.p0);

	    if (p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y))
		printf("%.2lf %.2lf %.2lf %.2lf\n", p1.x, p1.y, p2.x, p2.y);
	    else
		printf("%.2lf %.2lf %.2lf %.2lf\n", p2.x, p2.y, p1.x, p1.y);
	}	
    }    
}
