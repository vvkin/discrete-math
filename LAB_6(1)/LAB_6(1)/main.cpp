#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <numeric>
using namespace std;

template<typename T>
T** fill_matrix(const int, const int, const T);
template<typename T>
void delete_matrix(T**, const int);
void print_vector(vector<int>);

void get_input(const char*, int**&, int&, int&);
int* get_degrees(int**, const int);
bool euler_exist(int*, const int);
vector<int> get_euler(int**, const int);
int get_adjacent(int**, const int, const int);
void print_euler(int**, const int);


int main() {
	int** matrix = nullptr;
	int vertex_num, edges_num;
	get_input("input.txt", matrix, vertex_num, edges_num);

	print_euler(matrix, vertex_num);
	delete_matrix(matrix, vertex_num);
}

template<typename T>
T** fill_matrix(const int row_size, const int col_size, const T filler) {
	T** matrix = new T* [row_size];
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

void print_vector(vector<int> vec) {
	for (auto el : vec) {
		cout << el << " ";
	}
	cout << '\n';
}

void get_input(const char* file_name, int**& matrix, int& v_num, int& e_num){
	ifstream file_handler(file_name);
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

int* get_degrees(int** matrix, const int size){
	int* degrees = new int[size];
	for (auto i = 0; i < size; ++i) {
		degrees[i] = accumulate(matrix[i], matrix[i] + size, 0);
	}
	return degrees;
}

bool euler_exist(int* degrees, const int vertex_number) {
	int counter = 0;
	for (auto i = 0; i < vertex_number; ++i) {
		counter += (degrees[i] & 1);
		if (counter > 2) return false;
	}
	return true;
}

int get_adjacent(int** matrix, const int v, const int size){
	for (auto i = 0; i < size; ++i) {
		if (matrix[v][i] > 0) return i;
	}
	return size;
}

int get_start(int* degrees, const int v_num){
	for (auto i = 0; i < v_num; ++i)
		if (degrees[i]) return i;
}

void print_euler(int** matrix, const int v_num) {
	auto path = get_euler(matrix, v_num);
	if (path.size() == 0) {
		cout << "Euler path and circuit not exist!\n";
	}
	else{
		if (path.front() == path.back())
			cout << "Euler circuit : \n";
		else
			cout << "Euler path : \n";
		print_vector(path);
	}	
}

vector<int> get_euler(int** matrix, const int v_num){
	auto* deg = get_degrees(matrix, v_num);
	if (!euler_exist(deg, v_num))
		return vector<int>();

	stack<int> stack;
	vector<int> path;
	auto start = get_start(deg, v_num);
	stack.push(start);

	while (!stack.empty()) {
		const auto v = stack.top();
		const auto index = get_adjacent(matrix, v, v_num);
		if (index == v_num) {
			stack.pop();
			path.push_back(v + 1);
		}
		else {
			--matrix[v][index];
			--matrix[index][v];
			stack.push(index);
		}
	}
	delete[] deg;
	return path;
}


