#include "../point_class/polygon_ops.h"
#include <iostream>

using namespace std;

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





int main()
{
    std::ios_base::sync_with_stdio(false);

    int count{1};
    cin >> count;

    while (count != 0)
    {
	vector<Point_2d<int>> polygon;
	
	for (int v{0}; v < count; v++)
	{
	    int x, y;
	    cin >> x >> y;
	    polygon.push_back( Point_2d{x,y} );
	}

	if (polygon_clockwise(polygon))
	    cout << "CW ";
	else
	    cout << "CCW ";

	cout << polygon_area(polygon) << endl;

	cin >> count;
    }

    return 0;
}
