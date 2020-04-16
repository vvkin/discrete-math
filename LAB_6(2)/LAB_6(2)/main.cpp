#include <iostream>
#include <fstream>
#include <numeric>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
T** fill_matrix(const int, const int, const T);
template<typename T>
void delete_matrix(T**, const int);

int get_degree(int*, const int);
int* get_degrees(int**, const int);
void get_input(const char*, int**&, int&);
vector<list<int>> get_colors(int**, const int);
bool is_correct_color(int**,int*, const int, const int, const int);
int* get_vertex_order(int**, int*, const int);

void print_colors(int**, const int);


int main() {
	int** adj_matrix = nullptr;
	int v_num;
	get_input("input.txt", adj_matrix, v_num);
	print_colors(adj_matrix, v_num);
	delete_matrix(adj_matrix, v_num);
}

template<typename T>
T** fill_matrix(const int row_size, const int col_size, const T filler) {
	T** matrix = new T * [row_size];
	for (auto i = 0; i < row_size; ++i) {
		matrix[i] = new T[col_size];
	}
	for (auto i = 0; i < row_size; ++i) {
		for (auto j = 0; j < col_size; ++j) {
			matrix[i][j] = filler;
		}
	}
	return matrix;
}

template<typename T>
void delete_matrix(T** matrix, const int row_size) {
	for (auto i = 0; i < row_size; ++i) 
		delete[] matrix[i];
	delete[] matrix;
}

void get_input(const char* file_name, int**& matrix, int& v_num) {
	ifstream file_handler(file_name);
	int e_num;
	file_handler >> v_num >> e_num;
	matrix = fill_matrix(v_num, v_num, 0);

	for (auto i = 0; i < e_num; ++i) {
		int start, end;
		file_handler >> start >> end;
		matrix[start - 1][end - 1] += 1;
		matrix[end - 1][start - 1] += 1;
	}
	file_handler.close();
}

bool is_correct_color(int** adj_m, int* colors, const int v, const int color, const int v_num) {
	for (auto i = 0; i < v_num; ++i) {
		if (adj_m[v][i] && colors[i] == color)
			return false;
	}
	return true;
}

int* get_degrees(int** adj_m, const int size) {
	int* degrees = new int[size];
	for (auto i = 0; i < size; ++i) {
		degrees[i] = accumulate(adj_m[i], adj_m[i] + size, 0);
	}
	return degrees;
}

int* get_vertex_order(int** adj_m, int* degrees, const int v_num) {
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

vector<list<int>> get_colors(int** adj_m, const int v_num){
	vector<list<int> > color_set;
	auto* degrees = get_degrees(adj_m, v_num);
	const auto max_colors = get_degree(degrees, v_num);
	int* colors = new int[v_num];
	auto* order = get_vertex_order(adj_m, degrees, v_num);
	
	for (auto i = 0; i < v_num; ++i)
		colors[i] = -1;

	for (auto i = 0; i < v_num; ++i) {
		for (auto color = 0; color < max_colors; ++color) {
			if (is_correct_color(adj_m, colors, order[i], color, v_num)) {
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


int get_degree(int* deg, const int v_num) {
	return *max_element(deg, deg + v_num) + 1;
}

void print_colors(int** adj_m, const int v_num) {
	auto color_set = get_colors(adj_m, v_num);
	for (auto i = 0; i < color_set.size(); ++i) {
		cout << "Color " << i + 1 << '\n';
		for (auto el : color_set[i]) {
			cout << el + 1 << " ";
		}
		cout << '\n';
	}
}