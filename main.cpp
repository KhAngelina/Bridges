#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"
#include "Bridges.h"
#include "GraphBoost.h"

#include <algorithm>
#include <fstream>
#include <regex>
#define MAX_LINE_LEN 1000

std::unique_ptr<Graph> readGraph(const char *filename)
{
	FILE* f;
	char* line;
	char* p = NULL;
	f = fopen(filename, "r");
	if (f == NULL) {
		std::cout << filename << " - File Not Found!" << std::endl;
	}

	line = new char[MAX_LINE_LEN];
	int count = 0;
	int size = 0;

	do
	{
		fgets(line, MAX_LINE_LEN, f);
		if (count == 2)
		{
			std::string str(line);
			auto it = std::find_if(str.begin(), str.end(), isdigit);
			if (it != str.end()) size = std::atoi(str.c_str() + (it - str.begin()));
		}
		count++;
	} while (line[0] == '#');

	std::vector<std::vector<GraphUtils::Vertex>> graphVar(size);
	int a, b;
	while (!std::feof(f))
	{
		fgets(line, MAX_LINE_LEN, f);
		p = strtok(line, " ");
		a = atoi(p);
		p = strtok(NULL, " ");
		while (p == NULL)
		{
			p = strtok(NULL, " ");
		}
		b = atoi(p);
		graphVar[a].push_back(b);
	}

	delete[]line;
	fclose(f);

	return std::unique_ptr<Graph>(new Graph(graphVar));
}

void timeMeasure()
{
	std::ofstream resultfile;
	resultfile.open("tests.txt");

	int max_vertex = 650000;
	int vertex_plus = 100000;

	for (auto density_count = 40; density_count < 100; density_count += 10) {
		for (auto vertex_count = 10000; vertex_count <= max_vertex; vertex_count += vertex_plus) {
			std::unique_ptr<Graph> created_graph = createGraph(vertex_count, density_count);
			// std::unique_ptr<Graph> created_graph = readGraph("Email-Enron.txt");

			OneBridgeDet one_det(*created_graph);
			OneBridgeRand one_rand(*created_graph);
			TwoBridgeRand two_rand(*created_graph);

			std::cout << "Density: " << density_count << ", " << "Vertexes: " << vertex_count << std::endl;
			resultfile << density_count << "," << vertex_count << ",";

			auto time_one_det = one_det.findOneBridgeDet().second;
			resultfile << time_one_det << ",";
			std::cout << "One det DONE: " << time_one_det << std::endl;

			auto time_one_rand = one_rand.findOneBridgeRand().second;
			std::cout << "One rand DONE: " << time_one_rand << std::endl;
			resultfile << time_one_rand << ",";

			auto time_two_rand_std = two_rand.findTwoBridgeRand(0).second;
			std::cout << "Two rand std 32 DONE: " << time_two_rand_std << std::endl;
			resultfile << time_two_rand_std << ",";

			auto time_two_rand_radix = two_rand.findTwoBridgeRand(2).second;
			std::cout << "Two rand radix 32 DONE: " << time_two_rand_radix << std::endl;
			resultfile << time_two_rand_radix << ",";

			auto time_two_rand_bucket = two_rand.findTwoBridgeRand(1).second;
			std::cout << "Two rand bucket 32 DONE: " << time_two_rand_bucket << std::endl;
			resultfile << time_two_rand_bucket << ",";

#define INT_64
			auto time_two_rand_std_64 = two_rand.findTwoBridgeRand(0).second;
			std::cout << "Two rand std 64 DONE: " << time_two_rand_std_64 << std::endl;
			resultfile << time_two_rand_std_64 << ",";

			auto time_two_rand_radix_64 = two_rand.findTwoBridgeRand(2).second;
			std::cout << "Two rand radix 64 DONE: " << time_two_rand_radix_64 << std::endl;
			resultfile << time_two_rand_radix_64 << "\n";

			auto time_two_rand_bucket_64 = two_rand.findTwoBridgeRand(1).second;
			std::cout << "Two rand bucket 64 DONE: " << time_two_rand_bucket_64 << std::endl;
			resultfile << time_two_rand_bucket_64 << ",";

#undef INT_64
		}
	}

	resultfile.close();
}

int main()
{
	timeMeasure();

	return 0;
}
