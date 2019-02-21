#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  long items;
  cin >> items;

  vector<long> prices;
  for (long i{0}; i < items; i++)
    {
      long price;
      cin >> price;
      prices.push_back(price);
    }

  sort(prices.begin(), prices.end());

  long discount{0};
  long index{items - 1};
  while (index < items)
    {
      if (index - 2 >= 0)
	{
	  discount += prices.at(index - 2);
	  index -= 3;
	}
      else
	index = items;
    }

  cout << discount << endl;

  return 0;
}
