#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <numeric>
#include <list>
using namespace std;

template<typename T>
T** fill_matrix(const int, const int, const T);
template<typename T>
void delete_matrix(T**, const int);
void print_vector(vector<int>);

void get_input(const char*, int**&, int&);
int* get_degrees(int**, const int);

bool euler_exist(int*, const int);
vector<int> get_euler(int**, const int);
int get_adjacent(int**, const int, const int);
void print_euler(int**, const int);

list<int>* get_adj_list(int**, const int);
vector<int> try_to_make_cycle(vector<int>, list<int>*);
vector<int> get_hamilton(int**, const int);
void print_hamilton(int**, const int);

void show_menu();
void process_menu(int**, const int);


int main() {
	int** matrix = nullptr;
	int vertex_num;
	get_input("input.txt", matrix, vertex_num);

	process_menu(matrix, vertex_num);
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

void get_input(const char* file_name, int**& matrix, int& v_num){
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

int* get_degrees(int** matrix, const int size) {
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
		if (degrees[i] & 1) return i;
}

void print_euler(int** matrix, const int v_num) {
	auto path = get_euler(matrix, v_num);
	
	if (path.size() == 0) {
		cout << "Euler path and circuit don`t exist!\n";
	}
	else {
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

list<int>* get_adj_list(int** matrix, const int size) {
	auto* adj_list = new list<int>[size];
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			if (matrix[i][j]) {
				adj_list[i].push_back(j);
			}
		}
	}
	return adj_list;
}

vector<int> try_to_make_cycle(vector<int> path, list<int>* adj_list) {
	for (auto w : adj_list[path.back() - 1]) {
		if (w == path.front() - 1) {
			path.push_back(w + 1);
			break;
		}
	}
	return path;
}

vector<int> get_hamilton(int** matrix, const int v_num){
	auto* adj_list = get_adj_list(matrix, v_num);
	bool* visited = new bool[v_num];
	int start = 0;
	vector<int> path;
	
	for (auto i = 0; i < v_num; ++i) 
		visited[i] = false;

	visited[start] = true;
	path.push_back(start + 1);

	while (path.size() != 0 && path.size() != v_num) {
		start = path.back() - 1;
		for (auto w : adj_list[start]) {
			if (!visited[w]) {
				path.push_back(w + 1);
				visited[w] = true;
				break;
			}
		}
		if (path.back() - 1 == start) {
			path.pop_back();
		}
	}

	if (path.size()) 
		path = try_to_make_cycle(path, adj_list);
	delete[] visited;
	delete[] adj_list;
	return path;
}

void print_hamilton(int** matrix, const int size){
	auto path = get_hamilton(matrix, size);
	if (!path.size()) {
		cout << "Hamiltonian path and cycle don`t exist!\n";
	}
	else {
		if (path.front() == path.back()) {
			cout << "Hamiltonian cycle : \n";
		}
		else {
			cout << "Hamiltonuan path : \n";
		}
		print_vector(vector<int>(path));
	}
}

void show_menu(){
	cout << "Choose one of the following : \n"
		<< "1 - print Eulerian path or circuit\n"
		<< "2 - print Hamiltonian path or circuit\n";
}
	
void process_menu(int** matrix, const int v_num) {
	int choice = -1;

	show_menu();
	while (choice < 0 || choice > 2) {
		cout << "\nType you choice : ";
		cin >> choice;
	}
	if (choice == 1) {
		print_euler(matrix, v_num);
	}
	else {
		print_hamilton(matrix, v_num);
	}
}


