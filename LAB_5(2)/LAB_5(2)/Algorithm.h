#pragma once
#include "Graph.h"
#include <ostream>

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

class Algorithm{
private:
	static std::ostream* out;
	static bellman_result bellman(Graph&, int);
	static void print_path(int*, int, int);
	static dijkstra_result dijkstra(Graph&, int);
	static johnson_result johnson(Graph&);

	template<typename T>
	static void delete_matrix(T**, const int);
	template<typename T>
	static void print_matrix(T**, const int, const int);
public:
	static void print_path_between(Graph&, int, int);
	static void print_all_paths(Graph&, int);
	static void print_johnson_between(Graph&, int, int);
	static void print_all_johnson_paths(Graph&, int);
};

