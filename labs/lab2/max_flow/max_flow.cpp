#include <algorithm>
#include <vector>
#include <limits.h>
#include <functional>
#include <queue>

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

    /**
     * Resets the graphs state but not its connections and levels
     */
    void resetGraph()
	{
	    for (SIZE_T i{0}; i < graph.size(); i++)
	    {
		graph[i].level = -1;
		for (SIZE_T e{0}; e < graph[i].edges.size(); e++)
		{
		    graph[i].edges[e].curr_flow = 0;
		}
	    }
	}

    /**
     * Builds the levelgraph, must be called before running maxflow
     *
     * Time Complexity: O(n)
     */
    void build_level_graph()
	{
	    reset_level();
	    help_build_level_graph();
	}

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
    void connect(SIZE_T n1, SIZE_T n2, FLOW_T max_flow)
	{
	    if (n1 < graph.size() && n2 < graph.size())
	    {
		Edge e{n2, 0, max_flow};
		graph.at(n1).edges.push_back(e);
	    }
	    else
	    {
		throw std::out_of_range("Tried to add connection between nonesitant nodes");
	    }
	}

        int calculate_max_flow()
	{
	    FLOW_T result{0};
	    
	    FLOW_T prev_flow{-1};
	    FLOW_T max_flow{0};

	    while (prev_flow < max_flow)
	    {
		prev_flow = max_flow;
		
		build_level_graph();
		max_flow = update_flow(source, -1, 0);
		result += max_flow;
	    }

	    return result;
	    
	}

    struct Edge
    {
	SIZE_T end_node{-1};
	FLOW_T curr_flow{0};
	FLOW_T max_flow{0};
    };

    struct Node
    {	
	//Used to keep track of level in graph
	SIZE_T level{-1};
	std::vector<Edge> edges;
    };

    std::vector<Node>& get_graph()
	{
	    return graph;
	}

private:
  
    /**
     * Resets the levels in the graph
     *
     * Time Complexity: O(n)
     *
     * node: Current node
     */
    void reset_level()
	{
	    for (Node& n : graph)
		n.level = -1;
	}

    /**
     * Builds the level graph by performing a breadth first traversal
     * and setting the depth level in each node.
     *
     * Time Complexity: O(n)
     *
     * level: The current level
     * node : The current node
     */
    void help_build_level_graph()
	{
	    std::queue<SIZE_T> queue{};
	    queue.push(source);

	    SIZE_T curr_level{0};
	    graph[source].level = 0;

	    while (!queue.empty())
	    {
		SIZE_T node = queue.front();
		queue.pop();

		++curr_level;

		for (Edge& e : graph[node].edges)
		{
		    if (graph[e.end_node].level == -1 &&
			e.max_flow - e.curr_flow != 0)
		    {
			graph[e.end_node].level = curr_level;
			queue.push(e.end_node);
		    }
		}
	    }
	}

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
    FLOW_T update_flow(SIZE_T node, FLOW_T inc_flow, SIZE_T level)
	{
	    FLOW_T res{0};
	    for (Edge& e : graph[node].edges)
	    {
		if (graph[e.end_node].level == level + 1)
		{		    
		    FLOW_T flow{ e.max_flow - e.curr_flow };

		    if (flow > inc_flow &&
			inc_flow >= 0)
		    {
			flow = inc_flow;
		    }

		    if (e.end_node == sink)
		    {
			e.curr_flow += flow;
			return flow;
		    }

		    FLOW_T local_res = update_flow(e.end_node, flow, level + 1);

		    //Update edge flow and max flow to this node
		    e.curr_flow += local_res;
		    inc_flow -= local_res;

		    res += local_res;

		    //If node at max capacity return
		    if (inc_flow == 0)
			return res;

	        }
	    }
	    return res;
	}

    std::vector<Node> graph{};
    SIZE_T source;
    SIZE_T sink;
};

int main()
{
    long n, m, source, sink;

    scanf(" %ld", &n);
    scanf(" %ld", &m);
    scanf(" %ld", &source);
    scanf(" %ld", &sink);

    Max_flow<long, long> max_flow(n, source, sink);

    for (long e{0}; e < m; e++)
    {
	long u, v, c;
	scanf(" %ld", &u);
	scanf(" %ld", &v);
	scanf(" %ld", &c);
	
	max_flow.connect(u, v, c);
    }

    long max = max_flow.calculate_max_flow();

    std::vector<Max_flow<long, long>::Node>& graph = max_flow.get_graph();
    
    long count{0};
    for (Max_flow<long, long>::Node& n : graph)
    {
	for (Max_flow<long, long>::Edge e : n.edges)
	{
	    if (e.curr_flow > 0)
		count++;
	}
    }

    printf("%ld %ld %ld\n", n, max, count);

    for (long n{0}; n < graph.size(); n++)
    {
	for (Max_flow<long, long>::Edge edge : graph[n].edges)
	{
	    if (edge.curr_flow != 0)
	    {
		printf("%ld %ld %ld\n", n, edge.end_node, edge.curr_flow);
	    }
	}
    }
    
}
