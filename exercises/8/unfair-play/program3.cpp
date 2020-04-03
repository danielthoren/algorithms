#include <vector>
#include <cstdio>
#include <tuple>
#include <algorithm>

#include "max_flow.h"

using namespace std;


vector<int> unfair_play(vector<long>& scores, vector<pair<long, long>>& matches, long max_score)
{
    long size = 1 + matches.size() + scores.size();
    long win_team = scores.size() - 1;
    
    Max_flow<long, long> max_flow(size, 0, size - 1);
    
    const int match_offset{1};
    const int team_offset{ match_offset + matches.size() };
    
    for (int m{0}; m < matches.size(); m++)
    {
	if (matches[m].first != win_team && matches[m].second != win_team)
	{
	    max_flow.connect(0, m + match_offset, 2);
	}
    }

    for (int m{0}; m < matches.size(); m++)
    {
	if (matches[m].first != win_team && matches[m].second != win_team)
	{
	    max_flow.connect(m + match_offset, matches[m].first + team_offset, numeric_limits<long>::max());
	    max_flow.connect(m + match_offset, matches[m].second + team_offset, numeric_limits<long>::max());
	}
    }

    for (int t{0}; t < scores.size()-1; t++)
    {
	if (t != win_team)
	{
	    max_flow.connect(t + team_offset, size-1, max_score - scores[t+1] - 1);
	}
    }

    max_flow.calculate_max_flow();

    
}


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
	long max_score{0};
	for (long p{0}; p < m; p++)
	{
	    long a, b;
	    scanf(" %ld", &a);
	    scanf(" %ld", &b);

	    matches.push_back({a, b});

	    if (a == n || b == n)
		max_score += 2;
	}

	vector<ing> result = unfair_play(scores, matches, max_score + scores[n]);

	if (result.size() != 0)
	{	    
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
