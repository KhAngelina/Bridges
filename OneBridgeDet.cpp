#include <unordered_map>
#include <algorithm>
#include "Bridges.h"

void OneBridgeDet::dfs(GraphUtils::Vertex v) {
	std::stack<GraphUtils::Vertex> visit_vertex;
	visit_vertex.push(v);
	std::vector<bool> exited_vertex(m_graph.getVertexCount());

	while (!visit_vertex.empty()) {
		auto current_vertex = visit_vertex.top();

		if (!m_visited[current_vertex]) {
			m_visited[current_vertex] = true;

			m_time_enter[current_vertex] = m_min_enter[current_vertex] = m_timer++;

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

			if (m_parents[current_vertex] < m_graph.getVertexCount()) {
				m_min_enter[m_parents[current_vertex]] = std::min(m_min_enter[current_vertex], m_min_enter[m_parents[current_vertex]]);
			}

			for (auto neighbor : m_graph.getVertexNeighbours(current_vertex)) {
				if (neighbor == m_parents[current_vertex]) {
					continue;
				}

				m_min_enter[current_vertex] = std::min(m_min_enter[current_vertex], m_min_enter[neighbor]);
				//m_min_enter[current_vertex] = std::min(m_min_enter[current_vertex], m_time_enter[neighbor]);
			}
		}
		else {
			visit_vertex.pop();
		}
	}
}

std::pair<std::vector<GraphUtils::Edge>, double> OneBridgeDet::findOneBridgeDet() {
	std::fill(m_visited.begin(), m_visited.end(), false);
	std::fill(m_time_enter.begin(), m_time_enter.end(), -1);
	std::fill(m_min_enter.begin(), m_min_enter.end(), -1);
	std::vector<GraphUtils::Edge> bridges;

	auto start = std::chrono::system_clock::now();

	dfs(0);
	for (size_t vertex = 0; vertex < m_graph.getVertexCount(); ++vertex) {
		for (const auto& neighbor : m_graph.getVertexNeighbours(vertex)) {
			if (m_min_enter[neighbor] > m_time_enter[vertex] && m_parents[vertex] != neighbor) {
				bridges.push_back(GraphUtils::Edge{ vertex, neighbor });
			}
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	return std::make_pair(bridges, elapsed_seconds.count());
}
