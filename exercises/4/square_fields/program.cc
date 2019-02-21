
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int test_cases;
    cin >> test_cases;

    for (int test{0}; test < test_cases; test++){
	int n, k;
	cin >> n >> k;

	vector<pair<int, int>> points;
	for (int input{0}; input < n; input++)
	{
	    int x, y;
	    cin >> x >> y;
	    points.push_back({x,y});	    
	}

	//sort by x coord
	sort(points.begin(), points.end(), [] (pair<int, int> p1, pair<int, int> p2)
	     {
		 return p1.first < p2.first;
	     });

	int x_max = points.at(points.size() - 1).first;
	int x_min = points.at(0).first;
	int x_middle_val = (x_max - x_min) / 2;

	int x_size = max(x_max - x_middle_val, x_middle_val - x_min);

	//Sort by y coord
	sort(points.begin(), points.end(), [] (pair<int, int> p1, pair<int, int> p2)
	     {
		 return p1.second < p2.second;
	     });

	int y_max = points.at(points.size() - 1).second;
	int y_min = points.at(0).second;
	int y_middle_val = (y_max - y_min) / 2;

	int y_size = max(y_max - y_middle_val, y_middle_val - y_min);

	int square_size = min(x_size, y_size);
	cout << "Case #" << test << ": " << square_size << endl;
    }
}
