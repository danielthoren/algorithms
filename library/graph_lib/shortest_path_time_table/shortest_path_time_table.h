#include <algorithm>
#include <vector>
#include <limits.h>
#include <functional>

#ifndef SHORTEST_PATH_TIME_TABLE
#define SHORTEST_PATH_TIME_TABLE

/**
 * Author: Daniel Thorén
 *
 * Class that solves the shortest path problem with time tables. This
 * means that each edge can be traversed at times t0 + t*p for all
 * nonnegative integers.
 *
 * Template COST_T represents cost type, should be unsigned data type
 * Template INDEX_T represents index and time type, should be unsigned integer type
 */
template <typename COST_T, typename INDEX_T = long unsigned>
class Shortest_path_time_table
{
private:
    struct Edge;
    struct Node;
    
public:

    /**
     * Initializes the graph to the given size
     *
     * size: The size of the graph
     */
    Shortest_path_time_table(INDEX_T size) : graph(size)
	{}

    /**
     * Resets the graphs state but not its connections
     */
    void resetGraph();

    /**
     * Connects two nodes, node 1 and 2 with a one way edge with a given cost.
     * The connection is available at times t0 + t*p
     *
     * Time complexity: O(1)
     *
     * n1  : The node the edge leads from
     * N2  : The node the edge leads to
     * cost: The cost of traversing the edge
     * t0  : The first time the connection is available
     * p   : The interval at which the connection is available
     */
    void connect(INDEX_T n1, INDEX_T n2, COST_T cost, COST_T t0, COST_T p);
    
    /*
     * Returns the shortest path betwee the set start node and the
     * given end node. If there is no path between them it returns an
     * empty vector.
     *
     * Time complexity: O(n)
     *
     * end: The node to find path to
     */
    std::vector<INDEX_T> get_shortest_path(INDEX_T end);
    
    /**
     * Returns the shortest distance between the set start node and
     * the given end node. Returns INT_MAX if there is no path
     *
     * Time complexity: O(1)
     *
     * end: The node to measure the distance to
     */
    COST_T get_shortest_distance(INDEX_T end)
	{
	    return graph.at(end).min_cost;
	}
    

    /*
     * Searches the graph for the shortest path between start node and
     * every other node. After this method has been called the method
     * get_shortest_distance and get_shortest_path can be used to
     * query the graph
     *
     * Time complexity: O(n^2) (n = amount of nodes)
     *
     * start_node: The node from which to search
     */
    void dijkstras(INDEX_T start_node);

private:
    
    /**
     * If the following conditions are true for a neighbour node then
     * the cost of that node is updated:
     * -> The edge is available
     * -> The cost of the current node + the edge cost < neighbour nodes min_cost
     * -> The neighbour node has not been visited
     *
     * It also checks if it is worth waiting until an edge is available
     *
     * Time complexity: O(e) (worst case this node contains all edges)
     *
     * node_index: The index of the current node
     */
    void update_distance(Node& node);

    
    std::vector<Node> graph{};
    INDEX_T start;
};

#include "shortest_path_time_table.tcc"

#endif
