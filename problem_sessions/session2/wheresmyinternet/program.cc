#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

void print_sets(std::vector<int>& sets)
{
    for (int i = 0; i < sets.size(); i++)
	std::cout << "elem: " << i << " -> " << sets.at(i) << std::endl;
}

int compress_find(int elem, std::vector<int>& sets)
{
    std::vector<int> elems;
    while (sets.at(elem) != elem)
    {
	elems.push_back(elem);
	elem = sets.at(elem);
    }
    for (int e : elems)
	sets.at(e) = elem;
    return elem;
}

bool is_joined(int a, int b, std::vector<int>& sets)
{
    sets.at(a) = compress_find(a, sets);
    sets.at(b) = compress_find(b, sets);
    return sets.at(a) == sets.at(b);
}

void join(int a, int b, std::vector<int>& sets)
{   
    sets.at(compress_find(b, sets)) = compress_find(a, sets);
}

int main()
{
  int houses, cables;
  cin >> houses >> cables;

  vector<int> network(houses);
  iota(network.begin(), network.end(), 0);
  for (int i{0}; i < cables; i++)
    {
      int h1, h2;
      cin >> h1 >> h2;
      join(h1-1, h2-1, network);
    }

  vector<int> not_connected{};
  for (int j{0}; j < network.size(); j++)
    {
      if (! is_joined(0, j, network))
	not_connected.push_back(j);
    }

  if (not_connected.size() == 0)
    cout << "Connected" << endl;
  else
    for (int i{0}; i < not_connected.size(); i++)
      cout << not_connected.at(i) + 1 << endl;
  
}
