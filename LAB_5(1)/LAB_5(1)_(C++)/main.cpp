#include "Graph.h"
#include "Algorithm.h"
#include <fstream>
#include <iostream>


int main() {
	std::ifstream file_handler("input.txt");
	int n, m;
	file_handler >> n >> m;
	Graph graph(n);

	for (auto i = 0; i < m; ++i) {
		int start, end, weight;
		file_handler >> start >> end >> weight;
		graph.add_edge(start, end, weight);
	}

	file_handler.close();
	Algorithm::start_menu(graph);
}