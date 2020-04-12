#include "Algorithm.h"
#include <iostream>
#include <fstream>

int main() {
	std::ifstream file_handler("input.txt");
	int vertex_number, edges_number;
	file_handler >> vertex_number >> edges_number;
	Graph graph(vertex_number);

	for (auto i = 0; i < edges_number; ++i) {
		int start, end, weight;
		file_handler >> start >> end >> weight;
		graph.add_edge(start, end, weight);
	}
}