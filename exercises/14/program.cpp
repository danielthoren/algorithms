
#include <cstdio>

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

long n_over_k(long n, long k, vector<vector<long>>& triag)
{
    if (triag.size() > n)
	return triag[n][k];
    
    long i, j; 
  
    for (i = triag.size(); i <= n; i++) 
    {
	triag.push_back( vector<long>() );
	
        for (j = 0; j <= i; j++) 
        { 
            if (j == 0 || j == i)
	    {
                triag[i].push_back(1);
	    }
            else
	    {
                triag[i].push_back( triag[i - 1][j - 1] + 
				    triag[i - 1][j] );
	    }
        } 
    } 
  
    return triag[n][k]; 
}

template <typename T>
void help_subset_sum(std::vector<T> const& numbers,
		     T target,
		     std::vector<std::vector<T>>& result,
		     std::vector<T> subset,
		     T curr_index,
		     T curr_sum,
		     T min_elems,
		     T max_elems)
{
    if (curr_sum > target || subset.size() > max_elems)
    {
	return;
    }

    subset.push_back(numbers[curr_index]);

    if (curr_sum == target && subset.size() >= min_elems)
    {
	result.push_back(subset);
	return;
    }

    for (T i{curr_index + 1}; i < numbers.size(); i++)
    {
	help_subset_sum<T>(numbers, target, result, subset, i, curr_sum + numbers[i], min_elems, max_elems);
    }
}

template <typename T>
std::vector<std::vector<T>> subset_sum(std::vector<T>& numbers,
				       T target,
				       T min_elems = std::numeric_limits<T>::min(),
				       T max_elems = std::numeric_limits<T>::max())
{
    std::vector<T> subset{};
    
    std::vector<std::vector<T>> result{};

    std::sort(numbers.begin(), numbers.end());

    help_subset_sum<T>(numbers, target, result, subset, 0, numbers[0], min_elems, max_elems);

    return result;
}

template <typename T>
std::string print_subsets(std::vector<std::vector<T>> const& subset)
{
    std::stringstream stream{};
    
    for (std::vector<T> const& set : subset)
    {
	stream << "{";
	T sum{0};
	for (T i{0}; i < set.size() - 1; i++)
	{
	    sum += set[i];
	    stream << set[i] << ", ";
	}
	sum += set[set.size() - 1];
	stream << set[set.size() - 1] << "} = " << sum << std::endl;
    }
    return stream.str();
}


int main()
{
    vector<vector<long>> triag{};

    int g;
    scanf(" %d", &g);

    for (int i{0}; i < g; i++)
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

	long tot_ways = n_over_k(tile_count, pick, triag);

	vector<vector<long>> result = subset_sum(tiles, guess, pick);
	string res = print_subsets(result);

	printf(res.c_str());

	printf("Tot cases: %ld\n", tot_ways);
	printf("Successful cases: %ld\n", result.size());
	printf("Target: %ld\n", guess);
    }
    
}
