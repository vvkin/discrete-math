#include "Graph.h"


Graph::Graph(int vertex_number){
	this->vertex_number = vertex_number;
	fill_adj_matrix();
	adj_list = new std::list<edge>[vertex_number];
}

Graph::Graph(Graph& graph){
	vertex_number = graph.vertex_number;
	fill_adj_matrix();
	adj_list = new std::list<edge>[vertex_number];
}

Graph::~Graph(){
	delete[] adj_list;
	for (auto i = 0; i < vertex_number; ++i)
		delete[] adj_matrix[i];
	delete[] adj_matrix;
}

void Graph::add_edge(int start, int end, int weight) {
	adj_list[start - 1].push_back(edge(end - 1, weight));
	adj_matrix[start - 1][end - 1] = weight;
}

int** Graph::get_adj_matrix() {
	return adj_matrix;
}

bool Graph::contains_negative_edges()
{
	for (auto i = 0; i < vertex_number; ++i) {
		for (auto el : adj_list[i]) {
			if (el.weight < 0)
				return true;
		}
	}
	return false;
}

void Graph::fill_adj_matrix() {
	adj_matrix = new int* [vertex_number];
	for (auto i = 0; i < vertex_number; ++i)
		adj_matrix[i] = new int[vertex_number];

	for (auto i = 0; i < vertex_number; ++i) {
		for (auto j = 0; j < vertex_number; ++j) {
			adj_matrix[i][j] = INF;
		}
	}
}
