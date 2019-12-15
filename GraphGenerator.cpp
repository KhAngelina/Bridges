#include "graph.h"


std::unique_ptr<Graph> createGraph(int count_vertex, int prob) {
	std::vector<std::vector<GraphUtils::Vertex>> graph(count_vertex);

	for (int v = 0; v < count_vertex; ++v) {
		for (int i = v + 1; i < count_vertex - 1; ++i) {
			int rand_val = rand() % 100 + 1;

			if (prob >= rand_val)
			{
				graph[v].push_back(i);
				graph[i].push_back(v);
			}
		}
	}

	return std::unique_ptr<Graph>(new Graph(graph));
}