#pragma once
#include "graph.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <stack>

#ifdef INT_64
typedef int64_t myInt;
#else
typedef int32_t myInt;
#endif // INT_64

class Bridge {
public:
	Bridge(Graph& graph) : m_graph(graph)
	{
		m_visited.resize(graph.getVertexCount());
	};
	virtual void dfs(GraphUtils::Vertex v) = 0;

protected:
	Graph& m_graph;
	std::vector<bool> m_visited;
};

class OneBridgeDet : public Bridge {
public:
	OneBridgeDet(Graph& graph)
		: Bridge(graph),
		m_timer(0)
	{
		m_time_enter.resize(graph.getVertexCount());
		m_min_enter.resize(graph.getVertexCount());
		m_parents.resize(graph.getVertexCount(), graph.getVertexCount());
	};
	void dfs(GraphUtils::Vertex v);
	std::pair<std::vector<GraphUtils::Edge>, double> findOneBridgeDet();

protected:
	std::vector<int> m_time_enter;
	std::vector<int> m_min_enter;
	std::vector<GraphUtils::Vertex> m_parents;
	int m_timer;
};

class RandomBridge : public Bridge {
public:
	RandomBridge(Graph& graph)
		: Bridge(graph) {};
	
	int getEdgeValue(const GraphUtils::Vertex& from, const GraphUtils::Vertex& to)
	{
		return m_edges[std::min(from, to)][std::max(from, to)];
	};

	int getEdgeUpdated(const GraphUtils::Vertex& from, const GraphUtils::Vertex& to)
	{
		return m_edges_updated[std::min(from, to)][std::max(from, to)];
	};

	void setEdgeValue(const GraphUtils::Vertex& from, const GraphUtils::Vertex& to, int value)
	{
		m_edges[std::min(from, to)][std::max(from, to)] = value;
	};

	void setEdgeUpdated(const GraphUtils::Vertex& from, const GraphUtils::Vertex& to, bool value)
	{
		m_edges_updated[std::min(from, to)][std::max(from, to)] = value;
	};

	std::vector<GraphUtils::Edge> getEdges() {
		std::vector<GraphUtils::Edge> edge_list;
		for (auto it_firstLevel = m_edges.begin(); it_firstLevel != m_edges.end(); ++it_firstLevel) {
			for (auto it_secondLevel = it_firstLevel->second.begin(); it_secondLevel != it_firstLevel->second.end(); ++it_secondLevel) {
				if (it_firstLevel->first < it_secondLevel->first)
				{
					edge_list.push_back(GraphUtils::Edge(it_firstLevel->first, it_secondLevel->first));
				}
			}
		}
		return edge_list;
	};

	void dfs(GraphUtils::Vertex v)
	{
		std::stack<GraphUtils::Vertex> visit_vertex;
		visit_vertex.push(v);
		std::vector<bool> exited_vertex(m_graph.getVertexCount());
		std::vector<GraphUtils::Vertex> m_parents(m_graph.getVertexCount(), m_graph.getVertexCount());

		while (!visit_vertex.empty()) {
			auto current_vertex = visit_vertex.top();

			if (!m_visited[current_vertex]) {
				m_visited[current_vertex] = true;

				for (auto neighbor : m_graph.getVertexNeighbours(current_vertex)) {
					if (!m_visited[neighbor]) {
						m_parents[neighbor] = current_vertex;
						visit_vertex.push(neighbor);
					}
				}
			}
			else if (!exited_vertex[current_vertex]) {
				exited_vertex[current_vertex] = true;
				visit_vertex.pop();

				auto vertexSum = 0;
				for (auto neighbor : m_graph.getVertexNeighbours(current_vertex))
				{
					if (getEdgeUpdated(current_vertex, neighbor))
					{
						vertexSum ^= getEdgeValue(current_vertex, neighbor);
					}
					else
					{
						if (neighbor != m_parents[current_vertex])
						{
							setEdgeUpdated(current_vertex, neighbor, true);
							setEdgeValue(current_vertex, neighbor, (myInt)rand());
							vertexSum ^= getEdgeValue(current_vertex, neighbor);
						}
					}
				}

				if (m_parents[current_vertex] != m_graph.getVertexCount()) {
					setEdgeValue(current_vertex, m_parents[current_vertex], vertexSum);
					setEdgeUpdated(current_vertex, m_parents[current_vertex], true);
				}
			}
			else {
				visit_vertex.pop();
			}
		}
	}

protected:
	std::unordered_map<int, std::unordered_map<int, myInt> > m_edges;
	std::unordered_map<int, std::unordered_map<int, bool> > m_edges_updated;
};


class OneBridgeRand : RandomBridge {
public:
	OneBridgeRand(Graph& graph)
		:RandomBridge(graph) {};
	
	std::pair<std::vector<GraphUtils::Edge>, double> findOneBridgeRand();
};

class TwoBridgeRand : RandomBridge {
public:
	TwoBridgeRand(Graph& graph)
		:RandomBridge(graph) {};
	
	void radixSort(std::vector<GraphUtils::Edge>& e);
	int getMax(std::vector<GraphUtils::Edge>& e);
	void bucketSort(std::vector<GraphUtils::Edge>& e, const int buckets);
	std::pair<std::vector<std::vector<GraphUtils::Edge>>, double> findTwoBridgeRand(int sort_num = 0);
};