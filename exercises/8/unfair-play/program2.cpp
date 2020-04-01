#include <vector>
#include <cstdio>
#include <tuple>
#include <algorithm>

#include "max_flow.h"

using namespace std;

template<typename T>
class Baseball_elimination
{
public:
    Baseball_elimination(T win_team,
			 std::vector<std::pair<T,T>> const& matches,
			 std::vector<T> const& start_scores) :
	win_team{win_team},
	matches{matches},
	start_scores{start_scores},
	match_offset{1},
	team_offset{match_offset + matches.size() - 1},
	source{0},
	sink{matches.size() + start_scores.size() + 1},
	max_flow(matches.size() + start_scores.size() + 2, source, sink)
	{}
    

    enum Match{
	FirstWon, SecondWon, Tie
    };

    std::vector<Match>& get_result()
	{
	    return result;
	}

    bool is_eliminated()
	{        
	    //Connect all match nodes to source
	    for (T m{0}; m < matches.size(); m++)
	    {
		if (m != win_team)
		{
		    max_flow.connect(0, m + match_offset, WIN_SCORE);
		}
	    }

	    //The max remaining score that the win team can earn
	    T win_r{0};
    
	    //Connect match nodes to the two teams involved in said match
	    for (T m{0}; m < matches.size(); m++)
	    {
		if (matches[m].first == win_team || matches[m].second == win_team)
		{
		    win_r += WIN_SCORE;
		}
		else
		{
		    max_flow.connect(m + match_offset, matches[m].first + team_offset, std::numeric_limits<T>::max());
		    max_flow.connect(m + match_offset, matches[m].second + team_offset, std::numeric_limits<T>::max());
		}
	    }

	    T win_score{ win_r + start_scores[win_team] };

	    //Connect all team nodes to drain
	    for (T t{0}; t < start_scores.size(); t++)
	    {
		if (t != win_team)
		{
		    //Max remaining wins that team t is allowed to win
		    T max_win_remain{ win_score - start_scores[t] };
		    max_flow.connect(sink, t + team_offset, max_win_remain);
		}
	    }

	    T flow = max_flow.calculate_max_flow();

	    std::vector<typename Max_flow<T,T>::Node>& graph = max_flow.get_graph();

	    //Check if all edges from source to matches are saturated, if not
	    //then win_team cannot win, if they are then win_team can win
	    for (typename Max_flow<T,T>::Edge e : graph[0].edges)
	    {
		if (e.curr_flow != e.max_flow)
		{
		    return true;
		}
	    }

	    gen_result();
    
	    return false;
	}

private:

    void gen_result()
	{
	    std::vector<typename Max_flow<T,T>::Node> orig_graph = max_flow.get_orig_graph();

	    for (T m{0}; m < matches.size(); m++)
	    {
		if (matches[m].first == win_team)
		{
		    result.push_back(Match::FirstWon);
		}
		else if  (matches[m].second == win_team)
		{
		    result.push_back(Match::SecondWon);
		}
		else
		{
		    if(orig_graph[m + match_offset].edges[0].curr_flow == TIE_SCORE)
		    {
			result.push_back(Match::Tie);
		    }
		    else if (orig_graph[m + match_offset].edges[0].curr_flow == WIN_SCORE)
		    {
			if (orig_graph[m + match_offset].edges[0].end_node == matches[m].first)
			    result.push_back(Match::FirstWon);
			else
			    result.push_back(Match::SecondWon);
		    }
		    else
		    {
			if (orig_graph[m + match_offset].edges[1].end_node == matches[m].first)
			    result.push_back(Match::FirstWon);
			else
			    result.push_back(Match::SecondWon);
		    }
		}
	    }
	}
    
    T win_team{};
    std::vector<std::pair<T,T>> matches{};
    std::vector<T> start_scores{};
    
    T match_offset{};
    T team_offset{};

    std::vector<Match> result{};

    const T source{};
    const T sink{};

    Max_flow<T,T> max_flow{};

    const int WIN_SCORE = 2;
    const int TIE_SCORE = 1;
};


int main()
{
    long n, m;
    scanf(" %ld", &n);

    while (n != -1)
    {
	scanf(" %ld", &m);
	vector<int> scores{};
	scores.push_back(-1);
	for (int i{0}; i < n; i++)
	{
	    int score;
	    scanf(" %d", &score);
	    scores.push_back(score);
	}

	vector<pair<int,int>>matches{};
	for (int p{0}; p < m; p++)
	{
	    int a, b;
	    scanf(" %d", &a);
	    scanf(" %d", &b);

	    matches.push_back({a, b});
	}

	Baseball_elimination<int> elim(scores.size() - 1, matches, scores);
	bool eliminated{ elim.is_eliminated() };

	if (!eliminated)
	{
	    std::vector<Baseball_elimination<int>::Match>& result{ elim.get_result() };
	    if (result.size() > 0)
		printf("%d", result[0]);
	    for (int i{1}; i < m; i++)
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
