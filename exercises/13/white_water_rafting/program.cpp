#include <vector>

#include "Polygon.h"
#include "point.h"

using namespace std;

Polygon<double> get_poly()
{
    int pts;
    scanf(" %d", &pts);

    vector<point<double>> points;

    for (int p{0}; p < pts; p++)
    {
	double x, y;
	
	scanf(" %lf", &x);
	scanf(" %lf", &y);

	points.push_back( point<double>(x, y)  );	
    }

    return Polygon<double>(points);
}

int main()
{
    int cases;
    scanf(" %d", &cases);

    for (int c{0}; c < cases; c++)
    {
	Polygon<double> p1{ get_poly() };
	Polygon<double> p2{ get_poly() };

	auto res = p1.min_distance(p2);

	double dist = res.first.distance(res.second);

	printf("%lf\n", dist/2);	
    }
}
