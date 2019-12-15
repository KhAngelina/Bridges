#include "GraphBoost.h"

size_t GraphBoost::connectedComponents() {
	std::ios_base::sync_with_stdio(false);
	
	Mapping mappings;
	size_t n = boost::connected_components(g, boost::make_assoc_property_map(mappings));

	for (Component c = 0; c < n; ++c) {
		std::cout << "component " << c << ":";

		for (auto& mapping : mappings)
			if (mapping.second == c) std::cout << " " << mapping.first;

		std::cout << "\n";
	}

	return n;
}

void GraphBoost::addEdges(Graph& created_graph) {
	for (auto v = 0; v < created_graph.getVertexCount(); ++v) {
		for (auto neighbor : created_graph.getVertexNeighbours(v)) {
			boost::add_edge(v, neighbor, g);
		}
	}
}