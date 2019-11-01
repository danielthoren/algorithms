#include "polygon_ops.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);

    int count{1};
    cin >> count;

    while (count != 0)
    {
	vector<point<long double>> polygon;
	
	for (int v{0}; v < count; v++)
	{
	    long double x, y;
	    cin >> x >> y;
	    polygon.push_back( point<long double>{x,y} );
	}
	long double area = polygon_area(polygon);

	if (area <= 0)
	    cout << "CW ";
	else
	    cout << "CCW ";
	
	cout << fixed << setprecision(1) << std::abs(area) << endl;

	cin >> count;
    }

    return 0;
}
