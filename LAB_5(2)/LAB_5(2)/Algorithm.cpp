#include "Algorithm.h"
#include <iostream>
#include <iomanip>
#include <queue>


std::ostream* Algorithm::out = &std::cout;

template<typename T>
void Algorithm::print_matrix(T** matrix, const int row_size, const int col_size) {
	for (auto i = 0; i < row_size; ++i) {
		for (auto j = 0; j < col_size; ++j) {
			if (matrix[i][j] != INF)
				* out << std::setw(4) << matrix[i][j] << " ";
			else
				*out << std::setw(4) << "? ";
		}
		*out << '\n';
	}
}

template<typename T>
void Algorithm::delete_matrix(T** matrix, const int row_size) {
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

	for (auto& el : graph.adj_list) {
		if (dist[el.end] > dist[el.start] + el.weight) {
			delete[] dist;
			delete[] prev;
			return result;
		}
	}

	result.dist = dist;
	result.path = prev;

	return result;
}

void Algorithm::print_path(int* path, int start, int end) {
	auto current = end - 1;
	std::list<int> way;

	while (current != start - 1) {
		way.push_front(current + 1);
		current = path[current];
	}
	way.push_front(start);

	for (auto el : way) {
		if (el != way.back()) *out << el << "->";
		else *out << el;	
	}
}

void Algorithm::print_path_between(Graph& graph, int start, int end){
	auto result = bellman(graph, start - 1);

	if (result.dist == nullptr) {
		*out << "Graph contains negative cycles!\n";
		return;
	}
	
	if (result.dist[end - 1] != INF) {
		*out << "The distance between vertices is equal to " << result.dist[end - 1] << '\n';
		print_path(result.path, start, end);
	}
	delete[] result.dist;
	delete[] result.path;
}

void Algorithm::print_all_paths(Graph& graph, int start) {
	auto result = bellman(graph, start - 1);

	if (result.dist == nullptr) {
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

dijkstra_result Algorithm::dijkstra(Graph& graph, int start)
{
	struct compare {
		bool operator()(dest_edge& a, dest_edge& b) const {
			return a.weight > b.weight;
		}
	};

	dijkstra_result result;
	int* dist = new int[graph.vertex_number];
	int* path = new int[graph.vertex_number];
	std::priority_queue<dest_edge, std::vector<dest_edge>, compare> que;

	for (auto i = 0; i < graph.vertex_number; ++i) {
		dist[i] = INF;
	}

	que.push(dest_edge(start, 0));
	dist[start] = 0;

	while (!que.empty()) {
		auto u = que.top().destination; que.pop();

		for (auto& el : graph.dest_adj_list[u]) {
			if (dist[el.destination] > dist[u] + el.weight) {
				dist[el.destination] = dist[u] + el.weight;
				que.push(el);
			}
		}
	}
	result.dist = dist;
	result.path = path;
	return result;
}

johnson_result Algorithm::johnson(Graph& graph) {
	
	Graph new_graph(graph.vertex_number + 1);
	for (auto& el : graph.adj_list)
		new_graph.add_edge(el.start + 1, el.end + 1, el.weight);
	for (auto i = 0; i < graph.vertex_number; ++i)
		new_graph.add_edge(graph.vertex_number + 1, i + 1, 0);
	
	const int n = graph.vertex_number;
	johnson_result res;
	int** dist_m = new int* [n];
	int** path_m = new int* [n];

	auto bellman_res = bellman(new_graph, n);
	if (bellman_res.dist == nullptr) {
		delete[] dist_m;
		delete[] path_m;
		return res;
	}

	auto h = bellman_res.dist;
	
	--new_graph.vertex_number;
	for (auto& el : new_graph.adj_list) {
		if (el.start != n)
		{
			el.weight += h[el.start] - h[el.end];
		}
		
	}
	new_graph.rebuilt();

	for (auto i = 0; i < n; ++i) {
		auto result = dijkstra(new_graph, i);
		dist_m[i] = result.dist;
		path_m[i] = result.path;
	}

	for (auto i = 0; i < n; ++i){
		for (auto j = 0; j < n; ++j) {
			if (dist_m[i][j] != INF) {
				dist_m[i][j] += h[j] - h[i];
			}
		}
	}

	res.dist_m = dist_m;
	res.path_m = path_m;
	return res;
}

void Algorithm::print_johnson_between(Graph& graph, int start, int end) {
	
	auto result = johnson(graph);
	if (result.dist_m == nullptr) {
		*out << "Graph contains negative cycle!\n";
		return;
	}

	const int n = graph.vertex_number;
	*out << "The distance between vertices is equal to " << result.dist_m[start - 1][end - 1] << '\n';
	print_path(result.dist_m[start - 1], start, end);

	delete_matrix(result.dist_m, n);
	delete_matrix(result.path_m, n);
}

void Algorithm::print_all_johnson_paths(Graph& graph, int start){
	auto result = johnson(graph);
	if (result.dist_m == nullptr) {
		*out << "Graph contains negative cycle!\n";
	}
	const int n = graph.vertex_number;

	*out << "Distance matrix : \n";
	print_matrix(result.dist_m, n, n);
	*out << "History matrix : \n";
	print_matrix(result.path_m, n, n);
}
