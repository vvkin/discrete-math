#pragma once
#include "Graph.h"
#include <string>
#include <ostream>

struct dijkstra_result {
	int* path;
	int* dist;
};

struct floyd_result {
	int** dist_matrix;
	int** history_matrix;
};

class Algorithm{
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


