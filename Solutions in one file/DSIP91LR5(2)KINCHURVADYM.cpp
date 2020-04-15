#include <ostream>
#include <iostream>
#include <fstream>
#include <list>
#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>

const int INF = INT16_MAX;

struct dest_edge {
	int destination;
	int weight;

	dest_edge(int destination, int weight) {
		this->destination = destination;
		this->weight = weight;
	}
};


struct edge {
	int start, end, weight;

	edge(int start, int end, int weight) {
		this->start = start;
		this->end = end;
		this->weight = weight;
	}
};

class Graph
{
private:
	std::list<dest_edge>* dest_adj_list;
	std::list<edge> adj_list;
	int vertex_number;
	int** adj_matrix;

	void fill_adj_matrix();

public:
	Graph(int);
	Graph(Graph&);
	~Graph();
	void rebuilt();
	void add_edge(int, int, int);
	int** get_adj_matrix();
	bool contains_negative_edges();

	friend class Algorithm;
};


struct bellman_result {
	int* dist = nullptr;
	int* path = nullptr;
};

struct johnson_result {
	int** dist_m = nullptr;
	int** path_m = nullptr;
};

struct dijkstra_result {
	int* dist = nullptr;
	int* path = nullptr;
};

class Algorithm {
private:
	static std::ostream* out;
	static bellman_result bellman(Graph&, int);
	static void print_path(int*, int, int);
	static dijkstra_result dijkstra(Graph&, int);
	static johnson_result johnson(Graph&);

	static void print_path_between(Graph&, int, int);
	static void print_all_paths(Graph&, int);
	static void print_johnson_between(Graph&, int, int);
	static void print_all_johnson_paths(Graph&);

	template<typename T>
	static void delete_matrix(T**, const int);
	template<typename T>
	static void print_matrix(T**, const int, const int);

	static void do_work(Graph&);
	static void show_menu();


public:
	static void start_menu(Graph&);
};

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
	file_handler.close();
	Algorithm::start_menu(graph);
}

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

void Graph::rebuilt() {
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

std::ostream* Algorithm::out;

template<typename T>
void Algorithm::print_matrix(T** matrix, const int row_size, const int col_size) {
	for (auto i = 0; i < row_size; ++i) {
		for (auto j = 0; j < col_size; ++j) {
			if (matrix[i][j] != INF)
				* out << std::setw(4) << matrix[i][j];
			else
				*out << std::setw(4) << '?';
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
			if (dist[v] > dist[u] + edge_.weight && dist[u] != INF) {
				dist[v] = dist[u] + edge_.weight;
				prev[v] = u;
			}
		}
	}

	for (auto& el : graph.adj_list) {
		if (dist[el.end] != INF && dist[el.end] > dist[el.start] + el.weight) {
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
		if (el != way.back())* out << el << "->";
		else *out << el;
	}
}

void Algorithm::print_path_between(Graph& graph, int start, int end) {
	auto result = bellman(graph, start - 1);

	if (result.dist == nullptr) {
		*out << "Graph contains negative cycles!\n";
		return;
	}

	if (result.dist[end - 1] != INF) {
		*out << "The distance between vertices is equal to " << result.dist[end - 1] << '\n';
		print_path(result.path, start, end);
	}
	else {
		*out << "The path doesn`t exist!\n";
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
	delete[] result.dist;
	delete[] result.path;
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
		path[i] = -1;
	}

	que.push(dest_edge(start, 0));
	dist[start] = 0;

	while (!que.empty()) {
		auto u = que.top().destination; que.pop();

		for (auto& el : graph.dest_adj_list[u]) {
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

	for (auto i = 0; i < n; ++i) {
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
	if (result.dist_m[start - 1][end - 1] != INF) {
		*out << "The distance between vertices is equal to " << result.dist_m[start - 1][end - 1] << '\n';
		print_path(result.path_m[start - 1], start, end);
	}
	else {
		*out << "The path doesn`t exist!\n";
	}


	delete_matrix(result.dist_m, n);
	delete_matrix(result.path_m, n);
}

void Algorithm::print_all_johnson_paths(Graph& graph) {
	auto result = johnson(graph);
	if (result.dist_m == nullptr) {
		*out << "Graph contains negative cycle!\n";
		return;
	}
	const int n = graph.vertex_number;

	*out << "Distance matrix : \n";
	print_matrix(result.dist_m, n, n);

	delete_matrix(result.path_m, n);
	delete_matrix(result.dist_m, n);
}

void Algorithm::do_work(Graph& graph) {
	int input = -1, start, end;

	while (input < 1 || input > 4) {
		std::cout << "\nType your choice : ";
		std::cin >> input;
	}
	switch (input)
	{
	case 1:
		std::cout << "Print vertices to find path for : ";
		std::cin >> start >> end;
		print_path_between(graph, start, end);
		break;
	case 2:
		std::cout << "Type the start vertex : ";
		std::cin >> start;
		print_all_paths(graph, start);
		break;
	case 3:
		std::cout << "Type vertices to find path for : ";
		std::cin >> start >> end;
		print_johnson_between(graph, start, end);
		break;
	case 4:
		print_all_johnson_paths(graph);
		break;
	}
}

void Algorithm::show_menu() {
	std::cout << "Choose one of the next options : \n";
	std::cout << "1 - Find shortest path between two vertices with Ford - Bellman algorithm\n"
		<< "2 - Find shortest paths from source to other vertices with Ford - Bellman algorithm\n"
		<< "3 - Find shorted path between vertices with Johnson algorithm\n"
		<< "4 - Show shortest paths between all vertices with Johnson - Algorithm algorithm\n";
}

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
		*out << "\n";
		std::cout << "If you to exit print \'exit\' else press any key ...\n";
		std::cin >> answer;
		*out << '\n';
	}
	file.close();
}
