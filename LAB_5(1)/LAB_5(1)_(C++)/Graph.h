#pragma once
#include <list>

const int INF = 999999999;

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
	std::list<edge> *adj_list;
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

