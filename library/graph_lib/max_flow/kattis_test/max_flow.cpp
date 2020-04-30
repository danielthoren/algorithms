

#include "max_flow.h"

int main()
{
    long n, m, source, sink;

    scanf(" %ld", &n);
    scanf(" %ld", &m);
    scanf(" %ld", &source);
    scanf(" %ld", &sink);

    Max_flow<long> max_flow(n, source, sink);

    for (long e{0}; e < m; e++)
    {
	long u, v, c;
	scanf(" %ld", &u);
	scanf(" %ld", &v);
	scanf(" %ld", &c);
	
	max_flow.connect(u, v, c);
    }

    long max = max_flow.calculate_max_flow();

    std::vector<Max_flow<long, long>::Node> graph = max_flow.get_orig_graph();    
    
    
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
