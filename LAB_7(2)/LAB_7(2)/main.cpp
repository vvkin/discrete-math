#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
using namespace std;

void get_input(const char*, list<int>*&, int&);
int* get_bipartition(list<int>*, int);
vector<int> get_less_part(int*, int);
list<int>* get_new_list(vector<int>, list<int>*, int);

int* fill_array(int, int);

int main() {
	list<int>* adj_list = nullptr;
	int v_num;
	get_input("input.txt", adj_list, v_num);
}

void get_input(const char* file_name, list<int>*& adj_l, int& v_num) {
	ifstream file_handler(file_name);
	int e_num, start, end;
	adj_l = new list<int>[v_num];
	file_handler >> v_num >> e_num;

	for (auto i = 0; i < e_num; ++i) {
		file_handler >> start >> end;
		adj_l[start - 1].push_back(end - 1);
	}
	file_handler.close();
}

int* fill_array(int size, int filler) {
	int* arr = new int[size];
	for (auto i = 0; i < size; ++i)
		arr[i] = filler;
	return arr;
}

int* get_bipartition(list<int>* adj_l, int v_num) {
	auto* bipart = fill_array(v_num, -1);
	queue<int> que;
	que.push(0);

	while (!que.empty) {
		int start = que.front();
		que.pop();
		bipart[start] = 0;
		for (auto v : adj_l[start]) {
			if (bipart[v] == -1) {
				bipart[v] = !bipart[start];
				que.push(v);
			}
			else if (bipart[v] == 0) {
				return nullptr;
			}
		}
	}
	return bipart;
}

vector<int> get_less_part(int* bipart, int v_num) {
	vector<int> first, second;
	for (auto i = 0; i < v_num; ++i) {
		if (bipart[i]) first.push_back(i);
		else second.push_back(i);
	}
	delete[] bipart;
	return (first.size() > second.size()) ? first : second;
}

list<int>* get_new_list(vector<int> part, list<int>* adj_l, int v_num) {
	auto new_adj = new list<int>[v_num];
	for (auto start : part) {
		for (auto end : adj_l[start]) {
			new_adj[start].push_back(end);
		}
	}
	return new_adj;
}