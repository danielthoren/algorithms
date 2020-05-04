
#include <iostream>
#include <iomanip>

#include "polygon.h"

using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);

    int count{1};
    cin >> count;

    while (count != 0)
    {
	vector<dalg::Point<long double>> points;
    
	for (int v{0}; v < count; v++)
	{
	    long double x, y;
	    cin >> x >> y;
	    points.push_back( dalg::Point<long double>{x,y} );
	}
	dalg::Polygon<long double> poly(points);
	long double area = poly.get_area();

	if (area <= 0)
	    cout << "CW ";
	else
	    cout << "CCW ";
    
	//double area = (int)(polygon_area(polygon) * 10.0) / 10.0; //truncating at one decimal
	cout << fixed << setprecision(1) << std::abs(area) << endl;

	cin >> count;
    }

    return 0;
}

