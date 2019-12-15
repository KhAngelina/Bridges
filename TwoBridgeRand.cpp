#include <unordered_map>
#include <algorithm>
#include <cmath>

#include "Bridges.h"


int TwoBridgeRand::getMax(std::vector<GraphUtils::Edge>& e)
{
	int max = 0;
	for (auto i = 0; i < e.size(); ++i)
	{
		if (max < getEdgeValue(e[i].first, e[i].second))
		{
			max = getEdgeValue(e[i].first, e[i].second);
		}
	}
	return max;
}

void TwoBridgeRand::radixSort(std::vector<GraphUtils::Edge>& e)
{
	std::vector<GraphUtils::Edge> helper(e.size());

	int r = 8;
	int b = 0;
#ifdef INT_64
	b = 64;
#else
	b = 32;
#endif // INT_64

	std::vector<int> count(1 << r);
	std::vector<int> pref(1 << r);

	int groups = std::ceil(b / r);

	// the mask to identify groups 
	auto mask = (1 << r) - 1;

	for (auto c = 0, shift = 0; c < groups; c++, shift += r)
	{
		// reset count array 
		std::fill(count.begin(), count.end(), 0);

		// counting elements of the c-th group 
		for (auto i = 0; i < e.size(); ++i)
			count[(getEdgeValue(e[i].first, e[i].second) >> shift)&mask]++;

		// calculating prefixes 
		pref[0] = 0;
		for (auto i = 1; i < count.size(); ++i)
			pref[i] = pref[i - 1] + count[i - 1];

		// from e[] to helper[] elements ordered by c-th group 
		for (auto i = 0; i < e.size(); ++i)
			helper[pref[(getEdgeValue(e[i].first, e[i].second) >> shift)&mask]++] = e[i];

		for (auto i = 0; i < e.size(); ++i) {
			e[i] = helper[i];
		}
	}
}

void TwoBridgeRand::bucketSort(std::vector<GraphUtils::Edge>& e, const int buckets)
{
	std::vector<std::vector <GraphUtils::Edge>> b(buckets);

	auto max = getMax(e);
	auto max_div = max > 0 ? max : 1;

	for (auto i = 0; i < e.size(); ++i)
	{
		auto bi = (buckets - 1) * getEdgeValue(e[i].first, e[i].second) / max_div;
		b[bi].push_back(e[i]);
	}

	for (auto i = 0; i < buckets; ++i)
	{
		sort(b[i].begin(), b[i].end(), [&](const GraphUtils::Edge& left, const GraphUtils::Edge& right) {
			return getEdgeValue(left.first, left.second) < getEdgeValue(right.first, right.second);
		});
	}

	int index = 0;
	for (auto i = 0; i < buckets; ++i) {
		for (auto j = 0; j < b[i].size(); ++j) {
			e[index++] = b[i][j];
		}
	}
}

std::pair<std::vector<std::vector<GraphUtils::Edge>>, double> TwoBridgeRand::findTwoBridgeRand(int sort_num) {
	fill(m_visited.begin(), m_visited.end(), false);

	auto start = std::chrono::system_clock::now();

	dfs(0);

	auto edges = getEdges();

	switch (sort_num) {
	case 0: //std:sort
		sort(edges.begin(), edges.end(), [&](const GraphUtils::Edge& left, const GraphUtils::Edge& right) {
			return getEdgeValue(left.first, left.second) < getEdgeValue(right.first, right.second);
		});
		break;
	case 1: //bucket sort
		bucketSort(edges, edges.size());
		break;
	case 2: //radix sort
		radixSort(edges);
		break;
	default:
		break;
	}

	std::vector<std::vector<GraphUtils::Edge>> bridges;
	bridges.push_back({ edges[0] });

	int current_value = getEdgeValue(edges[0].first, edges[0].second);
	for (int i = 1; i < edges.size(); ++i) {
		const auto& edge = edges[i];
		if (getEdgeValue(edge.first, edge.second) == current_value)
		{
			bridges.back().push_back(GraphUtils::Edge(edge.first, edge.second));
		}
		else
		{
			bridges.push_back({ GraphUtils::Edge(edge.first, edge.second) });
			current_value = getEdgeValue(edge.first, edge.second);
		}
	}

	bridges.erase(std::remove_if(bridges.begin(), bridges.end(), [](const std::vector<GraphUtils::Edge>& edges) {return edges.size() < 2; }), bridges.end());

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	return std::make_pair(bridges, elapsed_seconds.count());
}