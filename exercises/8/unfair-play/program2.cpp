#include <vector>
#include <cstdio>
#include <tuple>
#include <algorithm>

#include "baseball_elimination.h"

using namespace std;

int main()
{
    long n, m;
    scanf(" %ld", &n);

    while (n != -1)
    {
	scanf(" %ld", &m);
	vector<long> scores{};
	scores.push_back(-1);
	for (long i{0}; i < n; i++)
	{
	    long score;
	    scanf(" %ld", &score);
	    scores.push_back(score);
	}

	vector<pair<long,long>>matches{};
	for (long p{0}; p < m; p++)
	{
	    long a, b;
	    scanf(" %ld", &a);
	    scanf(" %ld", &b);

	    matches.push_back({a, b});
	}

	Baseball_elimination<long> elim(scores.size() - 1, matches, scores);
	bool eliminated{ elim.is_eliminated() };

	if (!eliminated)
	{
	    std::vector<Baseball_elimination<long>::Match>& result{ elim.get_result() };
	    if (result.size() > 0)
		printf("%d", result[0]);
	    for (long i{1}; i < m; i++)
	    {
		printf(" %d", result[i]);
	    }
	    printf("\n");
	}
	else
	{
	    printf("NO\n");
	}
	
	scanf(" %ld", &n);
    }

    return 0;
}
