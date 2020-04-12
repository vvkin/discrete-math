#include "Algorithm.h"
#include <iostream>


std::ostream* Algorithm::out = &std::cout;

template<typename T>
T** Algorithm::create_matrix(int row_size, int col_size, T type) {
	T** matrix = new T * [row_size];
	for (auto i = 0; i < row_size; ++i)
		matrix[i] = new T[col_size];
	return matrix;
}

template<typename T>
T** Algorithm::fill_matrix(int row_size, int col_size, T filler) {
	T** matrix = new T * [row_size];
	
	for (auto i = 0; i < row_size; ++i) {
		matrix[i] = new T[col_size];
	}

	for (auto i = 0; i < row_size; ++i) {
		for (auto j = 0; j < col_size; ++j) {
			matrix[i][j] = filler;
		}
	} 

	return matrix;
}

template<typename T>
void Algorithm::delete_matrix(T** matrix, int row_size) {
	for (auto i = 0; i < row_size; ++i) delete[] matrix[i];
	delete[] matrix;
}

bellman_result Algorithm::bellman(Graph& graph, int start)
{
	bellman_result result;
	const int n = graph.vertex_number;
	int* dist = new int[n];
    int* prev = new int[n];

	for (auto i = 0; i < n; ++i) {
		dist[i] = INF;
		prev[i] = -1;
	}
	dist[start] = 0;

	for (auto i = 0; i < n - 1; ++i) {
		for (auto& edge_ : graph.adj_list) {
			int u = edge_.start, v = edge_.end;
			if (dist[v] > dist[u] + edge_.weight) {
				dist[v] = dist[u] + edge_.weight;
				prev[v] = u;
			}
		}
	}

	result.dist = dist;
	result.path = prev;

	return result;
}

bool Algorithm::constains_negative_cycles(std::list<edge> edges,int* dist) {
	for (auto& el : edges) {
		if (dist[el.end] > dist[el.start] + el.weight) {
			return true;
		}
	}
	return false;
}

void Algorithm::print_path(int* path, int start, int end) {
	auto current = end - 1;
	std::list<int> way;

	while (current != -1) {
		way.push_front(current + 1);
		current = path[current];
	}

	for (auto el : way) {
		if (el != way.back()) *out << el << "->";
		else *out << el;	
	}
}

void Algorithm::print_path_between(Graph& graph, int start, int end){
	auto result = bellman(graph, start - 1);

	if (constains_negative_cycles(graph.adj_list, result.dist)) {
		*out << "Graph contains negative cycles!\n";
		return;
	}
	
	if (result.dist[end - 1] != INF) {
		*out << "The distance between vertices is equal to " << result.dist[end - 1] << '\n';
		print_path(result.path, start, end);
	}
}

void Algorithm::print_all_paths(Graph& graph, int start) {
	auto result = bellman(graph, start - 1);

	if (constains_negative_cycles(graph.adj_list, result.dist)) {
		*out << "Graph contains negative cycles!\n";
		return;
	}

	for (auto i = 0; i < graph.vertex_number; ++i) {
		if (i != start - 1) {
			if (result.dist[i] == INF) {
				*out << "The distance between " << start << " and " << i + 1 << " is equal to infinity\n";
			}
			else {
				*out << "The distance between " << start << " and " << i + 1 << " is equal to " 
					 << result.dist[i] << '\n';
			}
		}
	}
}
