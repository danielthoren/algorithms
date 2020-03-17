#include "point.h"
#include "LineSegment.h"
#include <cstdio>
#include <variant>

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
    int cases{};
    
    scanf(" %d", &cases);

    for (int i{0}; i < cases; i++)
    {	
	LineSegment<long double> l1 = read_line();
	LineSegment<long double> l2 = read_line();

	auto res = l1.intersection(l2);


	if (std::holds_alternative<std::monostate>(res))
	{
	    printf("none\n");
	}
	else if (std::holds_alternative<point<long double>>(res))
	{
	    point<long double> pt = std::get<point<long double>>(res);
	    printf("%.2Lf %.2Lf\n", pt.x, pt.y);
	}
	else if (std::holds_alternative<LineSegment<long double>>(res))
	{
	    LineSegment<long double> lseg = std::get<LineSegment<long double>>(res);
	    point p1(lseg.p0);
	    point p2(lseg.u + lseg.p0);

	    if (p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y))
		printf("%.2Lf %.2Lf %.2Lf %.2Lf\n", p1.x, p1.y, p2.x, p2.y);
	    else
		printf("%.2Lf %.2Lf %.2Lf %.2Lf\n", p2.x, p2.y, p1.x, p1.y);
	}	
    }    
}
