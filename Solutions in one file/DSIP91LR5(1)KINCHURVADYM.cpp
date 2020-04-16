#include <string>
#include <ostream>
#include <list>
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <fstream>

const int INF =  999999999;

struct edge {
	int destination;
	int weight;

	edge(int destination, int weight) {
		this->destination = destination;
		this->weight = weight;
	}
};

class Graph
{
private:
	std::list<edge>* adj_list;
	int vertex_number;
	int** adj_matrix;

	void fill_adj_matrix();

public:
	Graph(int);
	Graph(Graph&);
	~Graph();
	void add_edge(int, int, int);
	int** get_adj_matrix();
	bool contains_negative_edges();

	friend class Algorithm;
};


struct dijkstra_result {
	int* path;
	int* dist;
};

struct floyd_result {
	int** dist_matrix;
	int** history_matrix;
};

class Algorithm {
private:
	static std::ostream* out;

	static dijkstra_result& dijkstra(Graph&, int);
	static floyd_result floyd(Graph&);
	static void print_way_between(dijkstra_result, int, int);
	static bool contains_negative_cycles(int, floyd_result);
	static void show_way_floyd(floyd_result, int, int);
	static void print_way(Graph&, int, int);
	static void print_all_ways(Graph&, int);
	static void print_floyd(Graph&);
	static void show_menu();
	static void do_work(Graph& graph);
	template<typename T>
	static void print_matrix(T**, int, int);
public:
	static void start_menu(Graph&);
};

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


Graph::Graph(int vertex_number) {
	this->vertex_number = vertex_number;
	fill_adj_matrix();
	adj_list = new std::list<edge>[vertex_number];
}

Graph::Graph(Graph& graph) {
	vertex_number = graph.vertex_number;
	fill_adj_matrix();
	adj_list = new std::list<edge>[vertex_number];
}

Graph::~Graph() {
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

struct compare {
	bool operator()(edge& a, edge& b) const {
		return a.weight > b.weight;
	}
};

std::ostream* Algorithm::out;

void Algorithm::start_menu(Graph& graph) {
	std::cout << "Do you want to work with file or console?(file/console)\n";
	std::string answer;
	std::cin >> answer;
	std::ofstream file;

	if (answer == "file") {
		std::cout << "Type the name of the file :\n";
		std::string file_name;
		std::cin >> file_name;
		file.open(file_name, std::ios::out);
		out = &file;
	}
	else out = &std::cout;

	while (answer != "exit") {
		show_menu();
		do_work(graph);
		std::cout << "If you to exit print \'exit\' else press any key ...\n";
		std::cin >> answer;
	}
	file.close();
}

dijkstra_result& Algorithm::dijkstra(Graph& graph, int start)
{
	dijkstra_result result;
	int* dist = new int[graph.vertex_number];
	int* path = new int[graph.vertex_number];
	std::priority_queue<edge, std::vector<edge>, compare> que;

	for (auto i = 0; i < graph.vertex_number; ++i) {
		dist[i] = INF;
		path[i] = -1;
	}

	que.push(edge(start, 0));
	dist[start] = 0;

	while (!que.empty()) {
		auto u = que.top().destination; que.pop();

		for (auto& el : graph.adj_list[u]) {
			if (dist[el.destination] > dist[u] + el.weight) {
				dist[el.destination] = dist[u] + el.weight;
				path[el.destination] = u;
				que.push(el);
			}
		}
	}

	result.dist = dist;
	result.path = path;

	return result;
}
template<typename T>
T** fill_matrix(int n, int m, T filler) {
	T** matrix = new T * [n];
	for (auto i = 0; i < n; ++i)
		matrix[i] = new T[m];

	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			matrix[i][j] = filler;
		}
	}

	return matrix;
}

floyd_result Algorithm::floyd(Graph& graph)
{
	auto n = graph.vertex_number;
	auto** dist = fill_matrix(n, n, INF);
	auto** history = fill_matrix(n, n, -1);
	auto** matrix = graph.get_adj_matrix();
	floyd_result result;

	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < n; ++j) {
			if (i == j) {
				dist[i][j] = 0;
				history[i][i] = 0;
			}
			else {
				dist[i][j] = matrix[i][j];
				history[i][j] = i + 1;
			}
		}
	}

	for (auto k = 0; k < n; ++k) {
		for (auto i = 0; i < n; ++i) {
			for (auto j = 0; j < n; ++j) {
				if (dist[k][k] < 0) {
					dist[k][k] = -INF;
					result.dist_matrix = dist;
					result.history_matrix = history;
					return result;
				}
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					history[i][j] = history[k][j];
				}
			}
		}
	}

	result.dist_matrix = dist;
	result.history_matrix = history;
	return result;
}

void Algorithm::print_way_between(dijkstra_result info, int start, int end) {
	std::vector<int> path;
	auto current = end - 1;

	while (current != -1) {
		path.push_back(current + 1);
		current = info.path[current];
	}

	std::reverse(path.begin(), path.end());
	for (auto i = 0; i < path.size(); ++i) {
		if (i == path.size() - 1)
			* out << path[i];
		else
			*out << path[i] << "->";
	}
}

bool Algorithm::contains_negative_cycles(int n, floyd_result info) {
	for (auto i = 0; i < n; ++i)
		if (info.dist_matrix[i][i] == -INF)
			return true;
	return false;
}

void Algorithm::show_way_floyd(floyd_result info, int start, int end) {
	std::vector<int> path;
	auto current = end;

	while (current != start) {
		path.push_back(current);
		current = info.history_matrix[start - 1][current - 1];
	};
	path.push_back(info.history_matrix[start - 1][current]);

	std::reverse(path.begin(), path.end());
	for (auto i = 0; i < path.size(); ++i) {
		if (i == path.size() - 1)
			* out << path[i];
		else
			*out << path[i] << "->";
	}
	*out << '\n';
}

void Algorithm::print_way(Graph& graph, int start, int end) {
	if (graph.contains_negative_edges()) {
		*out << "Graph containts negative edges! Using Dijkstra algorithm is impossible!\n";
		return;
	}

	auto info = dijkstra(graph, start - 1);
	if (info.dist[end - 1] != INF) {
		*out << "Distance between vertices is equal to " << info.dist[end - 1] << '\n';
		print_way_between(info, start, end);
	}

	delete[] info.path;
	delete[] info.dist;
}

void Algorithm::print_all_ways(Graph& graph, int start) {
	if (graph.contains_negative_edges()) {
		*out << "\nGraph containts negative edges! Using Dijkstra algorithm is impossible!\n";
		return;
	}

	auto info = dijkstra(graph, start - 1);
	for (auto i = 0; i < graph.vertex_number; ++i) {
		if (i != start - 1) {
			*out << "Shortest way from " << start << " to " << i + 1 << " is equal to ";
			if (info.dist[i] == INF)
				* out << "infinity\n";
			else
				*out << info.dist[i] << '\n';
		}
	}

	delete[] info.path;
	delete[] info.dist;
}

template<typename T>
void Algorithm::print_matrix(T** matrix, int n, int m) {
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			if (matrix[i][j] != INF)
				* out << std::setw(5) << matrix[i][j];
			else
				*out << std::setw(5) << "?";
		}
		*out << '\n';
	}
}

template<typename T>
void delete_matrix(T** matrix, int n) {
	for (auto i = 0; i < n; ++i)
		delete[] matrix[i];
	delete[] matrix;
}


void Algorithm::print_floyd(Graph& graph) {
	floyd_result info = floyd(graph);
	if (contains_negative_cycles(graph.vertex_number, info)) {
		*out << "\nGraph contains negative cycle!\n";
		return;
	}
	*out << "Distance matrix : \n";
	print_matrix(info.dist_matrix, graph.vertex_number, graph.vertex_number);
	*out << "History matrix :  \n";
	print_matrix(info.history_matrix, graph.vertex_number, graph.vertex_number);

	std::cout << "\nPrint vertices to find shortest way between for\n";
	int start, end;
	std::cin >> start >> end;

	if (info.dist_matrix[start - 1][end - 1] != INF) {
		*out << "\nThe distance is equal to " << info.dist_matrix[start - 1][end - 1] << '\n';
		show_way_floyd(info, start, end);
	}
	else
		*out << "\nPath between vertices doesn`t exist!\n";

	delete_matrix(info.dist_matrix, graph.vertex_number);
	delete_matrix(info.history_matrix, graph.vertex_number);
}

void Algorithm::show_menu() {
	std::cout << "Choose one of the next options : \n";
	std::cout << "1 - Find shortest path between two vertices with Dijkstra algorithm\n"
		<< "2 - Find shortest paths from source to other vertices with Dijkstra algorithm\n"
		<< "3 - Show shortest paths between all vertices with Floyd-Warshall algorithm\n";
}

void Algorithm::do_work(Graph& graph) {
	int input = -1, start, end;

	while (input < 1 || input > 3) {
		std::cout << "\nType your choice : ";
		std::cin >> input;
	}

	switch (input)
	{
	case 1:
		std::cout << "\nType start and end vertices : \n";
		std::cin >> start >> end;
		print_way(graph, start, end);
		*out << "\n\n";
		break;
	case 2:
		std::cout << "\nType start vertex : \n";
		std::cin >> start;
		print_all_ways(graph, start);
		*out << "\n\n";
		break;
	case 3:
		print_floyd(graph);
		*out << "\n\n";
		break;
	}
}
