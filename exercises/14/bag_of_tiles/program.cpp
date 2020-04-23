#include <cstdio>

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>

#include "n_over_k.h"
#include "subset_sum.h"

using namespace std;

int main()
{
    int g;
    scanf(" %d", &g);

    for (int i{1}; i <= g; i++)
    {
	long tile_count, pick, guess;
	scanf(" %ld", &tile_count);

	vector<long> tiles(tile_count);
	for (int ti{0}; ti < tile_count; ti++)
	{
	    long tile{};
	    scanf(" %ld", &tile);
	    tiles[ti] = tile;
	}

	scanf(" %ld", &pick);
	scanf(" %ld", &guess);

	if (pick == 0)
	{
	    if (guess == 0)
		printf("Game %d -- 1 : 0\n", i);
	    else
		printf("Game %d -- 0 : 1\n", i);

	    continue;
	}

	long tot_ways = n_over_k(tile_count, pick);       

	vector<vector<long>> result{ subset_sum(tiles, guess, pick) };

	printf("Game %d -- %ld : %ld\n", i, result.size(), tot_ways - result.size());
    }
    
}
