#ifndef BASEBALL_ELIMINATION
#define BASEBALL_ELIMINATION

#include <vector>

#include "max_flow.h"

namespace dalg
{

/**
 * Class containing functionality solving the baseball elimination
 * problem. A number of teams in a baseball leuge has already played
 * some matches. Given the current score of all teams and the
 * remaining matches is it possible for team x to win?
 *
 * The solution is based on the max flow problem. Create nodes for
 * each match and let an edge with max flow 2 (maximum points) flow
 * from source to each match. Then create one node for each team and
 * connect each match to the two teams meeting each other. The edges
 * between the matches and the teams in the match need no
 * limitation. Then create edges from each team to drain and limit the
 * amount of flow according to the max score that team x can gain.
 *
 * max_flow(e1) = max_score(x) - curr_score(e) - 1
 *
 * Then calculate max flow. If all edges from source ar fully
 * saturated (all flow is used) then team x can win. If not then team
 * x is eliminated.
 *
 */
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
	    FirstWon = 0,
	    Tie = 1,
	    SecondWon = 2
	};


	/**
	 * Calculates weather team x is eliminated. If it is the function
	 * returns true, otherwise false. It also generates the results of
	 * the match if it was possible for team x to win.
	 */
	bool is_eliminated();

	/**
	 * Returns one possible way for team x to win. For each match
	 * there is an integer with one of the following values:
	 *
	 * FirstWon(0) : Team nr 1 won the game, gets 2 points
	 * Tie(1)      : Draw, both teams gets 1 point
	 * SecondWon(2): Team nr 2 won the game, gets 2 points
	 *
	 * return: Vector containing matches of type "Match"
	 */
	std::vector<Match>& get_result()
	    {
		return result;
	    }



    private:

	void gen_result();
    
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
}

#include "baseball_elimination.tcc"

#endif
