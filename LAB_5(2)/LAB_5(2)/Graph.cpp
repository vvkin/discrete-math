#include "Graph.h"


Graph::Graph(int vertex_number) {
	this->vertex_number = vertex_number;
	fill_adj_matrix();
	dest_adj_list = new std::list<dest_edge>[vertex_number];
}

Graph::Graph(Graph& graph) {
	vertex_number = graph.vertex_number;
	fill_adj_matrix();
	dest_adj_list = new std::list<dest_edge>[vertex_number];
	
	for (auto i = 0; i < vertex_number; ++i) {
		for (auto j = 0; j < vertex_number; ++i) {
			if (graph.adj_matrix[i][j] != INF) {
				add_edge(i + 1, j + 1, adj_matrix[i][j]);
			}
		}
	}
}

Graph::~Graph() {
	delete[] dest_adj_list;
	for (auto i = 0; i < vertex_number; ++i)
		delete[] adj_matrix[i];
	delete[] adj_matrix;
}

void Graph::rebuilt(){
	for (auto i = 0; i < vertex_number; ++i) {
		dest_adj_list[i].clear();
	}
	for (auto& el : adj_list) {
		if (el.start < vertex_number) {
			dest_adj_list[el.start].push_back(dest_edge(el.end, el.weight));
			adj_matrix[el.start][el.end] = el.weight;
		}
	}
}


void Graph::add_edge(int start, int end, int weight) {
	dest_adj_list[start - 1].push_back(dest_edge(end - 1, weight));
	adj_list.push_back(edge(start - 1, end - 1, weight));
	adj_matrix[start - 1][end - 1] = weight;
}

int** Graph::get_adj_matrix() {
	return adj_matrix;
}

bool Graph::contains_negative_edges()
{
	for (auto el : adj_list) {
		if (el.weight < 0)
			return true;
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

