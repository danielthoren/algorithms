#include <vector>
#include <string>

#ifndef MAX_FLOW
#define MAX_FLOW

/**
 * Author: Daniel Thorén
 *
 * Class that solves the max flow problem. Implementation based on
 * Dinics Algorithm
 */
template<typename FLOW_T, typename SIZE_T = int>
class Max_flow
{
public:
    Max_flow(SIZE_T size, SIZE_T source, SIZE_T sink): graph(size), source{source}, sink{sink}
	{}
    
    struct Edge
    {
	SIZE_T end_node{-1};
	FLOW_T curr_flow{0};
	FLOW_T max_flow{0};
	bool residual_edge{false};
	// <index in graph, index in edges>	
	std::pair<SIZE_T, SIZE_T> back_edge{};
    };

    struct Node
    {	
	//Used to keep track of level in graph
	SIZE_T level{-1};
	std::vector<Edge> edges;
    };

    /**
     * Resets the graphs state but not its connections and levels
     */
    void resetGraph();

    /**
     * Connects node n1 to node n2 with the given max_flow throught
     * the edge
     *
     * Time Complexity: O(1)
     *
     * n1      : The node the edge leads from
     * N2      : The node the edge leads to
     * max_flow: The maximum flow from n1 to n2
     */
    void connect(SIZE_T n1, SIZE_T n2, FLOW_T max_flow);

    /**
     * Calculates the maximum flow in the graph. 
     *
     * Time complexity: O(E * V * V)
     * Memory complexity: O(E + V)
     *
     * return: The maximum flow from source to sink
     */
    FLOW_T calculate_max_flow();

    /**
     * Returns graph with residual edges
     */
    std::vector<Node>& get_graph() const;

    /**
     * Removes residual edges and returns clean graph
     */
    std::vector<Node> get_orig_graph() const;

    /**
     * Returns the graph as a string
     */
    std::string str();

private:

    /**
     * Resets the levels in the graph
     *
     * Time Complexity: O(n)
     *
     * node: Current node
     */
    void reset_level();

    /**
     * Builds the level graph by performing a breadth first traversal
     * and setting the depth level in each node.
     *
     * Time Complexity: O(n)
     *
     * level: The current level
     * node : The current node
     */
    bool build_level_graph();

    /**
     * Function giving the back edge to the given edge e
     */
    inline Edge& get_back_edge(Edge const& e);

        /**
     * Updates the flow in the graph by traversing the graph in a
     * breadth first manner, only visiting increasing levels. The
     * maximum posible increase in flow is updated and passed down
     * until sinc is found.
     *
     * Time Complexity: 
     *
     * node    : The current node
     * inc_flow: The maximum possible increase in flow
     * level   : The current level 
     *
     * return  : The increase in flow
     */
    FLOW_T update_flow(SIZE_T node, FLOW_T inc_flow, SIZE_T level);

    std::vector<Node> graph{};
    SIZE_T source;
    SIZE_T sink;
};

#include "max_flow.tcc"

#endif
