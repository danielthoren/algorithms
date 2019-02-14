
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int length, height;
  cin >> length >> height;

  vector<pair<int, int>> intervals{};
  
  bool upper = false;
  for (int i{0}; i < length; ++i)
    {
      int obs;
      cin >> obs;

      if (upper)
	intervals.push_back({obs, height - 1});
      else
	intervals.push_back({0, obs});      
    }

  for (pair<int, int> p : intervals)
    {
      
    }
  
  cout << obstacles << " " << paths << endl;

  return 0;
}
