#pragma once
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include "graph.h"

class GraphBoost {
	using G = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
	using Component = int;
	using Mapping = std::map<G::vertex_descriptor, Component>;
	G g;

public:
	GraphBoost(int V) : g(V) {}
	void addEdges(Graph& created_graph);
	size_t connectedComponents();
};