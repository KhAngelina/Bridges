#include <unordered_map>
#include <algorithm>

#include "graph.h"
#include "Bridges.h"


std::pair<std::vector<GraphUtils::Edge>, double> OneBridgeRand::findOneBridgeRand() {
	fill(m_visited.begin(), m_visited.end(), false);

	auto start = std::chrono::system_clock::now();
	/*for (auto i = m_visited.begin(); i != m_visited.end(); ++i) {
		if (!m_visited[*i])
		{
			dfs(*i);
		}
	}*/
	dfs(0);

	std::vector<GraphUtils::Edge> bridges;
	for (const auto& edge : getEdges()) {
		if (getEdgeValue(edge.first, edge.second) == 0)
		{
			bridges.push_back({ edge.first, edge.second });
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	return std::make_pair(bridges, elapsed_seconds.count());
}
