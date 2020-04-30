
#include <vector>
#include <queue>
#include <functional>
#include <limits.h>

#ifndef SHORTEST_PATH_NON_NEGATIVE
#define SHORTEST_PATH_NON_NEGATIVE

/**
 * Author: Daniel Thorén
 *
 * Class that solves the shortest path problem with non negative
 * weights. Contains a number of methods to query the graphx
 *
 * Template represents the cost type
 */
template <typename T>
class Shortest_path_non_negative
{
private:
    struct Edge;
    struct Node;
public:

    /**
     * Initializes the size of the graph
     *
     * size: The size of the graph
     */
    Shortest_path_non_negative(long unsigned size) : graph(size)
	{}

    /**
     * Resets the graphs state but not its connections
     */
    void resetGraph();

    /**
     * Connects two nodes, node 1 and 2 with a one way edge with a given cost
     *
     * Time complexity: O(1)
     *
     * n1  : The node the edge leads from
     * N2  : The node the edge leads to
     * cost: The cost of traversing the edge
     */
    void connect(long unsigned n1, long unsigned n2, T cost);    
    /*
     * Returns the shortest path betwee the set start node and the
     * given end node. If there is no path between them it returns an
     * empty vector.
     *
     * Time complexity: O(n)
     *
     * end: The node to find path to
     */
    std::vector<long unsigned> get_shortest_path(long unsigned end);
    
    /**
     * Returns the shortest distance between the set start node and
     * the given end node. Returns INT_MAX if there is no path
     *
     * Time complexity: O(1)
     *
     * end: The node to measure the distance to
     */
    long unsigned get_shortest_distance(long unsigned end);
    
    /*
     * Searches the graph for the shortest path between start node and
     * every other node. After this method has been called the method
     * get_shortest_distance and get_shortest_path can be used to
     * query the graph
     *
     * Time complexity: O(e + n * log n) (n = amount of nodes)
     *
     * start_node: The node from which to search
     */
    void dijkstras(long unsigned start_node);
    
private:

    /**
     * Comparator used in min queue
     */
    class Queue_comparator
    {
    public:
	Queue_comparator(std::vector<Node> const& graph) : graph{graph}
	    {}
	
	bool operator() (long unsigned n1, long unsigned n2)
	    {
		return graph[n1].min_cost > graph[n2].min_cost;
	    }

    private:
	std::vector<Node> const& graph;
    };

    /**
     * If the following conditions are true for a neighbour node then
     * the cost of that node is updated:
     * -> The cost of the current node + the edge cost < neighbour nodes min_cost
     * -> The neighbour node has not been visited
     *
     * Time complexity: O(e) (worst case this node contains all edges)
     *
     * node_index: The index of the current node
     */
    void update_distance(long unsigned node_index,
			 std::priority_queue<long unsigned, std::vector<long unsigned>, Queue_comparator>& min_queue);

    
    std::vector<Node> graph{};
    long unsigned start;
};

#include "shortest_path_non_negative.tcc"

#endif
