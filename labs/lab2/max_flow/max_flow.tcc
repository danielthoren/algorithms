#include <algorithm>
#include <limits.h>
#include <functional>
#include <queue>
#include <sstream>


template<typename FLOW_T, typename SIZE_T>
void Max_flow<FLOW_T, SIZE_T>::resetGraph()
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


template<typename FLOW_T, typename SIZE_T>
 void Max_flow<FLOW_T, SIZE_T>::connect(SIZE_T n1, SIZE_T n2, FLOW_T max_flow)
{
    if (n1 < graph.size() && n2 < graph.size())
    {
	Max_flow<FLOW_T, SIZE_T>::Edge e{n2, 0, max_flow, false};
		
	Max_flow<FLOW_T, SIZE_T>::Edge eb{n1, max_flow, max_flow, true};

	e.back_edge = {n2, graph.at(n2).edges.size()};
	eb.back_edge = {n1, graph.at(n1).edges.size()};

	graph.at(n1).edges.push_back(e);
	graph.at(n2).edges.push_back(eb);
    }
    else
    {
	throw std::out_of_range("Tried to add connection between nonesitant nodes");
    }
}


template<typename FLOW_T, typename SIZE_T>
 FLOW_T Max_flow<FLOW_T, SIZE_T>::calculate_max_flow()
{
    FLOW_T result{0};

    while (true)
    {		
	bool cont = build_level_graph();
	if (!cont)
	{
	    return result;
	}
		
	result += update_flow(source, -1, 0);
    }  
}


template<typename FLOW_T, typename SIZE_T>
std::vector<typename Max_flow<FLOW_T, SIZE_T>::Node>& Max_flow<FLOW_T, SIZE_T>::get_graph()
{
    return graph;
}


template<typename FLOW_T, typename SIZE_T>
std::vector<typename Max_flow<FLOW_T, SIZE_T>::Node> Max_flow<FLOW_T, SIZE_T>::get_orig_graph() const
{
    std::vector<Node> copy{graph};

    for (Node& n : copy)
    {		
	n.edges.erase(std::remove_if(n.edges.begin(), n.edges.end(),
				     [] (Max_flow<FLOW_T, SIZE_T>::Edge const& e)
					 {
					     return e.residual_edge;
					 }), n.edges.end());
    }
	    
    return copy;
}    


template<typename FLOW_T, typename SIZE_T>
 std::string Max_flow<FLOW_T, SIZE_T>::str()
{
    std::stringstream sstream{};

    for (int n{0}; n < graph.size(); n++)
    {
	sstream << n << ": Level: " << graph[n].level << " Edges: ";
	for (Max_flow<long, long>::Edge& e : graph[n].edges)
	{
	    sstream << "{end_node: "
		    << e.end_node
		    << " Residual: "
		    << e.residual_edge
		    << " curr_flow: "
		    << e.curr_flow
		    << " max_flow: "
		    << e.max_flow << "}";
	}
	sstream << std::endl;
    }
    return sstream.str();
}


template<typename FLOW_T, typename SIZE_T>
 void Max_flow<FLOW_T, SIZE_T>::reset_level()
{
    for (Max_flow<FLOW_T, SIZE_T>::Node& n : graph)
	n.level = -1;
}


template<typename FLOW_T, typename SIZE_T>
 bool Max_flow<FLOW_T, SIZE_T>::build_level_graph()
{
    reset_level();

    //contains <node index, expected level>
    std::queue<std::pair<SIZE_T, SIZE_T>> queue{};
    queue.push({source, 0});

    bool found_sink{false};

    while (!queue.empty())
    {
	std::pair<SIZE_T, SIZE_T> node = queue.front();
	queue.pop();

	if (graph[node.first].level == -1 ||
	    graph[node.first].level > node.second)
	{		
	    graph[node.first].level = node.second;
		    
	    for (Max_flow<FLOW_T, SIZE_T>::Edge& e : graph[node.first].edges)
	    {
		if ((graph[e.end_node].level == -1 ||
		     graph[e.end_node].level > node.second) &&
		    e.max_flow - e.curr_flow != 0)
		{
		    queue.push( {e.end_node, node.second + 1} );
		    if (e.end_node == sink)
		    {
			found_sink = true;
		    }
		}
	    }
	}
    }
    return found_sink;
}


template<typename FLOW_T, typename SIZE_T>
inline typename Max_flow<FLOW_T, SIZE_T>::Edge&
Max_flow<FLOW_T, SIZE_T>::get_back_edge (Max_flow<FLOW_T, SIZE_T>::Edge const& e)
{
    return graph[ e.back_edge.first ].edges[ e.back_edge.second ];
}


template<typename FLOW_T, typename SIZE_T>
 FLOW_T Max_flow<FLOW_T, SIZE_T>::update_flow(SIZE_T node, FLOW_T inc_flow, SIZE_T level)
{
    FLOW_T res{0};
    for (Max_flow<FLOW_T, SIZE_T>::Edge& e : graph[node].edges)
    {
	FLOW_T flow{ e.max_flow - e.curr_flow };
	
	if (graph[e.end_node].level == level + 1 && flow != 0)
	{		    
	    if (flow > inc_flow &&
		inc_flow >= 0)
	    {
		flow = inc_flow;
	    }

	    if (e.end_node == sink)
	    {
		e.curr_flow += flow;
		get_back_edge(e).curr_flow -= flow;
		return flow;
	    }

	    FLOW_T local_res = update_flow(e.end_node, flow, level + 1);

	    //Update edge flow and max flow to this node
	    e.curr_flow += local_res;
	    get_back_edge(e).curr_flow -= local_res;
		    
	    inc_flow -= local_res;

	    res += local_res;

	    //If node at max capacity return
	    if (inc_flow == 0)
		return res;

	}
    }
    return res;
}
