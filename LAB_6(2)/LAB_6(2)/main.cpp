#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

void get_input(const char*, list<int>*&, int&);

template<typename T>
T* fill_array(const T, const int);

int get_degree(int*, const int);
int* get_degrees(list<int>*, const int);
vector<list<int>> get_colors(list<int>*, const int);
bool is_correct_color(list<int>*, int*, const int, const int, const int);
int* get_vertex_order(int*, const int);



void print_colors(list<int>*, const int);

int main() {
	int v_num;
	list<int>* adj_list = nullptr;
	get_input("input.txt", adj_list, v_num);
	print_colors(adj_list, v_num);
	delete[] adj_list;
}

template<typename T>
T* fill_array(const T filler, const int size) {
	T* arr = new T[size];
	for (auto i = 0; i < size; ++i)
		arr[i] = filler;
	return arr;
}

void get_input(const char* file_name, list<int>*& adj_list, int& v_num) {
	ifstream file_handler(file_name);
	int e_num;
	file_handler >> v_num >> e_num;
	adj_list = new list<int>[v_num];

	for (auto i = 0; i < e_num; ++i) {
		int start, end;
		file_handler >> start >> end;
		adj_list[start - 1].push_back(end - 1);
		adj_list[end - 1].push_back(start - 1);
	}
	file_handler.close();
}

bool is_correct_color(list<int>* adj_l, int* colors, const int v, const int color, const int v_num) {
	for (auto vertex : adj_l[v]) {
		if (colors[vertex] == color)
			return false;
	}
	return true;
}

int* get_degrees(list<int>* adj_l, const int v_num) {
	int* degrees = new int[v_num];
	for (auto v = 0; v < v_num; ++v) {
		degrees[v] = adj_l[v].size();
	}
	return degrees;
}

int get_degree(int* deg, const int v_num) {
	return *max_element(deg, deg + v_num) + 1;
}

int* get_vertex_order(int* degrees, const int v_num) {
	int* order = new int[v_num];
	for (auto i = 0; i < v_num; ++i)
		order[i] = i;

	for (auto i = 0; i < v_num; ++i) {
		for (auto j = v_num - 1; j > i; --j) {
			if (degrees[j] > degrees[j - 1]) {
				swap(degrees[j], degrees[j - 1]);
				swap(order[j], order[j - 1]);
			}
		}
	}
	return order;
}

vector<list<int>> get_colors(list<int>* adj_l, const int v_num) {
	vector<list<int> > color_set;
	auto* degrees = get_degrees(adj_l, v_num);
	const auto max_colors = get_degree(degrees, v_num);
	auto* colors = fill_array(-1, v_num);
	auto* order = get_vertex_order(degrees, v_num);

	for (auto i = 0; i < v_num; ++i) {
		for (auto color = 0; color < max_colors; ++color) {
			if (is_correct_color(adj_l, colors, order[i], color, v_num)) {
				if (color >= color_set.size())
					color_set.push_back(list<int>{});
				colors[order[i]] = color;
				color_set[color].push_back(order[i]);
				break;
			}
		}
	}
	delete[] degrees;
	delete[] colors;
	delete[] order;
	return color_set;
}

void print_colors(list<int>* adj_l, const int v_num) {
	auto color_set = get_colors(adj_l, v_num);
	for (auto i = 0; i < color_set.size(); ++i) {
		cout << "Color " << i + 1 << '\n';
		for (auto el : color_set[i]) {
			cout << el + 1 << " ";
		}
		cout << '\n';
	}
}