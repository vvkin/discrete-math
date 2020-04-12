#pragma once
#include "Graph.h"
#include <ostream>

struct bellman_result {
	int* dist;
	int* path;
};

class Algorithm{
private:
	static std::ostream* out;
	static bellman_result bellman(Graph&, int);
	static void print_path(int*, int, int);
	
	template<typename T> 
	static T** fill_matrix(int, int, T);
	template<typename T>
	static void delete_matrix(T**, int);
	template<typename T>
	static T** create_matrix(int, int, T);
public:
	static void print_path_between(Graph&, int, int);

};

