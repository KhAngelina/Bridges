#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

#include "GraphUtils.h"

class Graph
{
public:
	Graph(std::vector<std::vector<GraphUtils::Vertex>> vertex_list) : m_graph(vertex_list) {};
	int getVertexCount() { return m_graph.size(); }
	std::vector<GraphUtils::Vertex> &getVertexNeighbours(GraphUtils::Vertex vertex) { return m_graph[vertex]; }
	
	void deleteEdge(GraphUtils::Vertex vertex1, GraphUtils::Vertex vertex2) {
		m_graph[vertex1].erase(std::remove(m_graph[vertex1].begin(), m_graph[vertex1].end(), vertex2), m_graph[vertex1].end());
		m_graph[vertex2].erase(std::remove(m_graph[vertex2].begin(), m_graph[vertex2].end(), vertex1), m_graph[vertex2].end());
	};
	
	void printGraph() {
		std::ios_base::sync_with_stdio(false);
		for (auto vert : m_graph)
		{
			for (auto neighbor : vert)
			{
				std::cout << neighbor << ' ';
			}
			std::cout << std::endl;
		}
	};

private:
	std::vector<std::vector<GraphUtils::Vertex>> m_graph;
};

std::unique_ptr<Graph> createGraph(int count_vertex, int prob);