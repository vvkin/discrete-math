#pragma once
#include <list>

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

