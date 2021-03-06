
#include <algorithm>
#include <functional>

#ifndef SHORTEST_PATH_NON_NEGATIVE
#error 'shortest_path_non_negative.tcc' is not supposed to be included directly. Include 'shortest_path_non_negative.h' instead.
#endif

template <typename T>
struct Shortest_path_non_negative<T>::Edge
{
    long unsigned end_node;
    T cost;
};


template <typename T>
struct Shortest_path_non_negative<T>::Node
{
    long unsigned index;
    T min_cost;
    bool visited;
    long unsigned parent;
    std::vector<Edge> edges;
};

template <typename T>
void Shortest_path_non_negative<T>::resetGraph()
{
    for (size_t i{0}; i < graph.size(); i++)
    {
	graph.at(i).min_cost = INT_MAX;
	graph.at(i).visited = false;
	graph.at(i).index = i;
    }
}


template <typename T>
void Shortest_path_non_negative<T>::connect(long unsigned n1, long unsigned n2, T cost)
{
    if (n1 < graph.size() && n2 < graph.size())
    {
	Edge e{n2, cost};
	graph.at(n1).edges.push_back(e);
    }
    else
    {
	throw std::out_of_range("Tried to add connection between nonexsitant nodes");
    }
}


template <typename T>
std::vector<long unsigned> Shortest_path_non_negative<T>::get_shortest_path(long unsigned end)
{
    std::vector<long unsigned> path{};
    long unsigned curr = end;
    long unsigned i{0};
    for (; curr != start && i < graph.size(); i++)
    {
	path.insert(path.begin(), curr);
	curr = graph.at(curr).parent;
    }
    if (i == graph.size())
    {		
	return std::vector<long unsigned>();
    }
	    
    path.insert(path.begin(), start);
    return path;
}


template <typename T>
long unsigned Shortest_path_non_negative<T>::get_shortest_distance(long unsigned end)
{
    return graph.at(end).min_cost;
}

template <typename T>
void Shortest_path_non_negative<T>::dijkstras(long unsigned start_node)
{
    resetGraph();

    graph.at(start_node).min_cost = 0;  
    
    //each pair stores {index, cost when inserted}
    std::priority_queue
	<std::pair<long unsigned, T>,
	 std::vector<std::pair<long unsigned, T>>,
	 Shortest_path_non_negative<T>::Queue_comparator> min_queue;
    
    min_queue.push( std::pair<long unsigned, T>{start_node, graph[start_node].min_cost} );

    while (!min_queue.empty())
    {
	long unsigned min_node = min_queue.top().first;
	min_queue.pop();

	if (! graph.at(min_node).visited)
	{
	    update_distance(min_node, min_queue);
	}
    }
}


template <typename T>
void Shortest_path_non_negative<T>::update_distance(long unsigned node_index,
						    std::priority_queue
						    <std::pair<long unsigned, T>,
						    std::vector<std::pair<long unsigned, T>>,
						    Shortest_path_non_negative<T>::Queue_comparator>& min_queue)
{
    Node& node = graph.at(node_index);
    if (node.min_cost != INT_MAX)
    {
	for (Edge& edge: node.edges)
	{
	    T tmp = node.min_cost + edge.cost;
	    if (tmp < graph.at(edge.end_node).min_cost &&
		!graph.at(edge.end_node).visited)
	    {
		graph.at(edge.end_node).min_cost = tmp;

		min_queue.push( {edge.end_node, graph[edge.end_node].min_cost} );
		//Enable backtracking of path
		graph.at(edge.end_node).parent = node_index;
	    }
	}
	node.visited = true;
    }
}
