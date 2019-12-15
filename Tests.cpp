//#include "graph.h"
//#include "GraphUtils.h"
//#include "Bridges.h"
//#include "GraphBoost.h"
//
//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//#include "catch.hpp"
//
//bool Equal(std::vector<GraphUtils::Edge>& expected, std::vector<GraphUtils::Edge>& actual) {
//	if (expected.size() != actual.size()) {
//		std::cout << "Expected and actual size is different\n";
//		return false;
//	}
//
//	for (auto i = 0; i < expected.size(); ++i) {
//		bool check_1 = true;
//		if (std::find(actual.begin(), actual.end(), expected[i]) == actual.end()) {
//			check_1 = false;
//		}
//
//		bool check_2 = true;
//		GraphUtils::Edge tmp_edge(expected[i].second, expected[i].first);
//		if (std::find(actual.begin(), actual.end(), tmp_edge) == actual.end()) {
//			check_2 = false;
//		}
//
//		if (!check_1 && !check_2) {
//			std::cout << "Not all expected edges were found\n";
//			return false;
//		}
//	}
//
//	return true;
//}
//
//std::vector<std::vector<std::vector<GraphUtils::Vertex>>> data_oneBridge = {
//	{ {1, 2}, {0, 2}, {0, 1, 3}, {2} },
//	{ {4}, {4}, {}, {4, 5}, {0, 1, 3}, {3} },
//	{ {1, 2}, {0, 2}, {0, 1} },
//	{ {1}, {0} }
//};
//
//std::vector<std::vector<GraphUtils::Edge>> expected_data_oneBridge = {
//	{ GraphUtils::Edge(2, 3) },
//	{ GraphUtils::Edge(0, 4), GraphUtils::Edge(4, 1), GraphUtils::Edge(4, 3), GraphUtils::Edge(3, 5) },
//	{ },
//	{ GraphUtils::Edge(0, 1) }
//};
//
//TEST_CASE("One bridge_determenistic works", "one_determenistic") {
//	for (auto test_case = 0; test_case < data_oneBridge.size(); ++test_case) {
//		Graph test_graph(data_oneBridge[test_case]);
//		OneBridgeDet test(test_graph);
//
//		auto actual_result = (test.findOneBridgeDet()).first;
//
//		REQUIRE(Equal(expected_data_oneBridge[test_case], actual_result));
//	}
//}
//
//std::vector<GraphUtils::Edge> checkConnectedComponentsNumber(Graph & created_graph) {
//	std::vector<GraphUtils::Edge> bridges;
//	
//	GraphBoost graph_boost_before(created_graph.getVertexCount());
//	graph_boost_before.addEdges(created_graph);
//
//	size_t number_before = graph_boost_before.connectedComponents();
//	
//	std::vector<GraphUtils::Edge> used_edges;
//
//	for (auto v = 0; v < created_graph.getVertexCount(); ++v) {
//		for (auto neighbor : created_graph.getVertexNeighbours(v)) {
//			if (std::find(used_edges.begin(), used_edges.end(), GraphUtils::Edge(std::min(v, neighbor), std::max(v, neighbor))) == used_edges.end()) {
//				Graph tmp_graph = created_graph;
//				
//				tmp_graph.deleteEdge(v, neighbor);
//				used_edges.push_back(GraphUtils::Edge(std::min(v, neighbor), std::max(v, neighbor)));
//
//				GraphBoost graph_boost_after(tmp_graph.getVertexCount());
//				graph_boost_after.addEdges(tmp_graph);
//
//				size_t number_after = graph_boost_after.connectedComponents();
//
//				if (number_after > number_before) {
//					bridges.push_back(GraphUtils::Edge(v, neighbor));
//				}
//			}
//		}
//	}
//
//	return bridges;
//}
//
//TEST_CASE("One bridge_determenistic (STRESS TEST) works", "one_determenistic (STRESS TEST)") {
//	for (auto density_count = 50; density_count < 100; density_count += 10) {
//		for (auto vertex_count = 10; vertex_count <= 100; vertex_count += 10) {
//			std::unique_ptr<Graph> created_graph = createGraph(vertex_count, density_count);
//
//			OneBridgeDet one_det(*created_graph);
//			auto result_one_det = (one_det.findOneBridgeDet()).first;
//
//			auto result_handle = checkConnectedComponentsNumber(*created_graph);
//
//			REQUIRE(Equal(result_handle, result_one_det));
//		}
//	}
//}
//
//TEST_CASE("One bridge_randomized works", "one_randomized") {
//	for (auto test_case = 0; test_case < data_oneBridge.size(); ++test_case) {
//		Graph test_graph(data_oneBridge[test_case]);
//		OneBridgeRand test(test_graph);
//
//		auto actual_result = (test.findOneBridgeRand()).first;
//
//		REQUIRE(Equal(expected_data_oneBridge[test_case], actual_result));
//	}
//}
//
//TEST_CASE("One bridge_randomized (STRESS TEST) works", "one_randomized (STRESS TEST)") {
//	for (auto density_count = 50; density_count < 100; density_count += 10) {
//		for (auto vertex_count = 10; vertex_count <= 100; vertex_count += 10) {
//			std::unique_ptr<Graph> created_graph = createGraph(vertex_count, density_count);
//
//			OneBridgeRand one_rand(*created_graph);
//			auto result_one_rand = (one_rand.findOneBridgeRand()).first;
//
//			auto result_handle = checkConnectedComponentsNumber(*created_graph);
//
//			REQUIRE(Equal(result_handle, result_one_rand));
//		}
//	}
//}
//
//bool Equal_two(std::vector< std::vector<GraphUtils::Edge>>& expected, std::vector< std::vector<GraphUtils::Edge>>& actual) {
//	if (expected.size() != actual.size()) {
//		std::cout << "Expected and actual size is different\n";
//		return false;
//	}
//
//	for (auto i = 0; i < expected.size(); ++i) {
//		for (auto j = 0; j < expected[i].size(); ++j) {
//			bool check_1 = true;
//			if (std::find(actual[i].begin(), actual[i].end(), expected[i][j]) == actual[i].end()) {
//				check_1 = false;
//			}
//
//			bool check_2 = true;
//			GraphUtils::Edge tmp_edge(expected[i][j].second, expected[i][j].first);
//			if (std::find(actual[i].begin(), actual[i].end(), tmp_edge) == actual[i].end()) {
//				check_2 = false;
//			}
//
//			if (!check_1 && !check_2) {
//				std::cout << "Not all expected edges were found\n";
//				return false;
//			}
//		}
//	}
//
//	return true;
//}
//std::vector<std::vector<std::vector<GraphUtils::Vertex>>> data_twoBridge = {
//	{ {1, 2}, {0, 2, 3, 4 }, {0, 1, 3, 4 }, { 1, 2, 4 }, {1, 2, 3} },
//	{ {1, 2}, {0, 2}, {0, 1} },
//	{ {1}, {0} }
//};
//
//std::vector<std::vector<std::vector<GraphUtils::Edge>>> expected_data_twoBridge = {
//	{ { GraphUtils::Edge(0, 1), GraphUtils::Edge(0, 2) } },
//	{ { GraphUtils::Edge(0, 1), GraphUtils::Edge(0, 2), GraphUtils::Edge(1, 2) } },
//	{ }
//};
//
//TEST_CASE("Two bridge_randomized works", "two_randomized") {
//	for (auto test_case = 0; test_case < data_twoBridge.size(); ++test_case) {
//		for (auto sort_num = 2; sort_num < 3; ++sort_num) {
//			Graph test_graph(data_twoBridge[test_case]);
//			TwoBridgeRand test(test_graph);
//
//			auto actual_result = (test.findTwoBridgeRand(sort_num)).first;
//
//			REQUIRE(Equal_two(expected_data_twoBridge[test_case], actual_result));
//		}
//	}
//}
//
//std::vector< std::vector<GraphUtils::Edge>> checkConnectedComponentsNumberTwo(Graph & created_graph) {
//	std::vector<std::vector<GraphUtils::Edge>> bridges;
//
//	GraphBoost graph_boost_before(created_graph.getVertexCount());
//	graph_boost_before.addEdges(created_graph);
//
//	size_t number_before = graph_boost_before.connectedComponents();
//
//	std::vector<GraphUtils::Edge> used_edges;
//
//	for (auto v = 0; v < created_graph.getVertexCount(); ++v) {
//		for (auto neighbor : created_graph.getVertexNeighbours(v)) {
//			if (std::find(used_edges.begin(), used_edges.end(), GraphUtils::Edge(std::min(v, neighbor), std::max(v, neighbor))) == used_edges.end()) {
//				Graph tmp_graph = created_graph;
//
//				tmp_graph.deleteEdge(v, neighbor);
//				used_edges.push_back(GraphUtils::Edge(std::min(v, neighbor), std::max(v, neighbor)));
//
//				bridges.push_back({ GraphUtils::Edge(v, neighbor) });
//
//				for (auto second_neighbor : created_graph.getVertexNeighbours(neighbor)) {
//					Graph tmp_graph_2 = tmp_graph;
//					tmp_graph_2.deleteEdge(neighbor, second_neighbor);
//
//					GraphBoost graph_boost_after(tmp_graph_2.getVertexCount());
//					graph_boost_after.addEdges(tmp_graph_2);
//
//					size_t number_after = graph_boost_after.connectedComponents();
//
//					if (number_after > number_before) {
//						bridges.back().push_back(GraphUtils::Edge(std::min(neighbor, second_neighbor), std::max(neighbor, second_neighbor)));
//					}
//				}
//			}
//		}
//	}
//
//	bridges.erase(std::remove_if(bridges.begin(), bridges.end(), [](const std::vector<GraphUtils::Edge>& edges) {return edges.size() < 2; }), bridges.end());
//
//	return bridges;
//}
//
//bool Equal_two_set(std::set<GraphUtils::Edge>& expected,std::set<GraphUtils::Edge>& actual) {
//	if (expected.size() != actual.size()) {
//		std::cout << "Expected and actual size is different\n";
//		return false;
//	}
//
//	for (auto it = expected.begin(); it != expected.end(); ++it) {
//		bool check_1 = true;
//		if (std::find(actual.begin(), actual.end(), *it) == actual.end()) {
//			check_1 = false;
//		}
//
//		bool check_2 = true;
//		GraphUtils::Edge tmp_edge((*it).second, (*it).first);
//		if (std::find(actual.begin(), actual.end(), tmp_edge) == actual.end()) {
//			check_2 = false;
//		}
//
//		if (!check_1 && !check_2) {
//			std::cout << "Not all expected edges were found\n";
//			return false;
//		}
//	}
//
//	return true;
//}
//
//std::set<GraphUtils::Edge> createSet(std::vector< std::vector<GraphUtils::Edge>>& vec) {
//	std::vector<GraphUtils::Edge> result_vector;
//	for (auto element : vec) {
//		result_vector.insert(
//			result_vector.end(),
//			std::make_move_iterator(element.begin()),
//			std::make_move_iterator(element.end())
//		);
//	}
//	
//	return std::set<GraphUtils::Edge> (result_vector.begin(), result_vector.end());
//}
//
//TEST_CASE("Two bridge_randomized_std (STRESS TEST) works", "two_randomized_std (STRESS TEST)") {
//	int sort_num = 0;
//	
//	for (auto density_count = 50; density_count < 55; density_count += 10) {
//		for (auto vertex_count = 5; vertex_count <= 10; vertex_count += 10) {
//			std::unique_ptr<Graph> created_graph = createGraph(vertex_count, density_count);
//
//			TwoBridgeRand two_rand(*created_graph);
//			auto result_two_rand = (two_rand.findTwoBridgeRand(sort_num)).first;
//			auto result_two_rand_set = createSet(result_two_rand);
//
//			auto result_handle = checkConnectedComponentsNumberTwo(*created_graph);
//			auto result_handle_set = createSet(result_handle);
//
//			REQUIRE(Equal_two_set(result_handle_set, result_two_rand_set));
//		}
//	}
//}
//
//TEST_CASE("Two bridge_randomized_bucket (STRESS TEST) works", "two_randomized_bucket (STRESS TEST)") {
//	int sort_num = 1;
//
//	for (auto density_count = 50; density_count < 55; density_count += 10) {
//		for (auto vertex_count = 5; vertex_count <= 10; vertex_count += 10) {
//			std::unique_ptr<Graph> created_graph = createGraph(vertex_count, density_count);
//
//			TwoBridgeRand two_rand(*created_graph);
//			auto result_two_rand = (two_rand.findTwoBridgeRand(sort_num)).first;
//			auto result_two_rand_set = createSet(result_two_rand);
//
//			auto result_handle = checkConnectedComponentsNumberTwo(*created_graph);
//			auto result_handle_set = createSet(result_handle);
//
//			REQUIRE(Equal_two_set(result_handle_set, result_two_rand_set));
//		}
//	}
//}
//
//TEST_CASE("Two bridge_randomized_radix (STRESS TEST) works", "two_randomized_radix (STRESS TEST)") {
//	int sort_num = 2;
//
//	for (auto density_count = 50; density_count < 55; density_count += 10) {
//		for (auto vertex_count = 5; vertex_count <= 10; vertex_count += 10) {
//			std::unique_ptr<Graph> created_graph = createGraph(vertex_count, density_count);
//
//			TwoBridgeRand two_rand(*created_graph);
//			auto result_two_rand = (two_rand.findTwoBridgeRand(sort_num)).first;
//			auto result_two_rand_set = createSet(result_two_rand);
//
//			auto result_handle = checkConnectedComponentsNumberTwo(*created_graph);
//			auto result_handle_set = createSet(result_handle);
//
//			REQUIRE(Equal_two_set(result_handle_set, result_two_rand_set));
//		}
//	}
//}