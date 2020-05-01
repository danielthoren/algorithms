
#include <functional>
#include <limits.h>
#include <algorithm>

#ifndef SHORTEST_PATH_TIME_TABLE
#error 'shortest_path_time_table.tcc' is not supposed to be included directly. Include 'shortest_path_time_table.h' instead.
#endif

template <typename COST_T, typename INDEX_T>
struct Shortest_path_time_table<COST_T, INDEX_T>::Edge
{
    INDEX_T end_node;
    COST_T cost;
    COST_T t0;
    COST_T p;
};


template <typename COST_T, typename INDEX_T>
struct Shortest_path_time_table<COST_T, INDEX_T>::Node
{
    COST_T min_cost;
    bool visited;
    INDEX_T parent;
    std::vector<Edge> edges;
};


template <typename COST_T, typename INDEX_T>
void Shortest_path_time_table<COST_T, INDEX_T>::resetGraph()
{
    for (long unsigned i{0}; i < graph.size(); i++)
    {
	graph.at(i).min_cost = INT_MAX;
	graph.at(i).visited = false;
    }
}


template <typename COST_T, typename INDEX_T>
void Shortest_path_time_table<COST_T, INDEX_T>::connect(INDEX_T n1, INDEX_T n2, COST_T cost, COST_T t0, COST_T p)
{
    if (n1 < graph.size() && n2 < graph.size())
    {
	Edge e{n2, cost, t0, p};
	graph.at(n1).edges.push_back(e);
    }
    else
    {
	throw std::out_of_range("Tried to add connection between nonesitant nodes");
    }
}


template <typename COST_T, typename INDEX_T>
std::vector<INDEX_T> Shortest_path_time_table<COST_T, INDEX_T>::get_shortest_path(INDEX_T end)
{
    std::vector<INDEX_T> path{};
    INDEX_T curr = end;
    long unsigned i{0};
    for (; curr != start && i < graph.size(); i++)
    {
	path.insert(path.begin(), curr);
	curr = graph.at(curr).parent;
    }
    if (i == graph.size())
    {		
	return std::vector<INDEX_T>();
    }
	    
    path.insert(path.begin(), start);
    return path;
}


template <typename COST_T, typename INDEX_T>
void Shortest_path_time_table<COST_T, INDEX_T>::dijkstras(INDEX_T start_node)
{
    resetGraph();
    start = start_node;
	    
    graph.at(start_node).min_cost = 0;
    INDEX_T prev_node = start_node;
    for (long unsigned i{0}; i < graph.size(); i++)
    {
	INDEX_T min_node = std::numeric_limits<INDEX_T>::max();
	for (long unsigned n{0}; n < graph.size(); n++)
	{
	    if (!graph.at(n).visited)
	    {
		if (min_node == std::numeric_limits<INDEX_T>::max() ||
		    graph.at(n).min_cost < graph.at(min_node).min_cost)
		{
		    min_node = n;
		}
	    }
	}
	graph.at(min_node).parent = prev_node;
	prev_node = min_node;
	update_distance(graph.at(min_node));
    }
}


template <typename COST_T, typename INDEX_T>
void Shortest_path_time_table<COST_T, INDEX_T>::update_distance(Node& node)
{
    if (node.min_cost != INT_MAX)
    {
	for (Edge edge: node.edges)
	{
	    COST_T tmp = node.min_cost + edge.cost;

	    //Adding time until edge available to cost
	    if (edge.p == 0 && node.min_cost > edge.t0)
	    {
		tmp = INT_MAX;	    
	    }
	    else if (node.min_cost < edge.t0)
	    {
		tmp += edge.t0 - node.min_cost;
	    }
	    else if (edge.p != 0 && (node.min_cost - edge.t0) % edge.p != 0)
	    {
		tmp += edge.p - ((node.min_cost - edge.t0) % edge.p);
	    }
	    
	    if (tmp < graph.at(edge.end_node).min_cost &&
		!graph.at(edge.end_node).visited)
	    {
		graph.at(edge.end_node).min_cost = tmp;
	    }
	}
	node.visited = true;
    }
}
