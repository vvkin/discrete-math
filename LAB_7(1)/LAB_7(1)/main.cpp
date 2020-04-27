#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <regex>
using namespace std;

void get_input(const char*, list<int>*&, int&);
int* get_parents(list<int>*, int);
int* get_prufer_code(list<int>*, int);
int get_pointer(int*, int, int);
int* get_degrees(list<int>*, int);
void print_array(int*, int);
string read_code(const char*);
vector<int> convert_to_int(string);
int* fill_array(int, int);
int** fill_matrix(int, int);
int* degree_from_code(vector<int>, int);
int** decode_tree(vector<int>);
void print_matrix(int**, int);
void show_menu();
void work_with_answer(int);
void process_menu();
void delete_matrix(int**, int);
void print_matrix(int**, int);

int main() {
	process_menu();
}

void get_input(const char* file_name, list<int>*& adj_l, int& v_num) {
	ifstream file_handler(file_name);
	int e_num, start, end;
	file_handler >> v_num >> e_num;
	adj_l = new list<int>[v_num];
	for (auto i = 0; i < e_num; ++i) {
		file_handler >> start >> end;
		adj_l[start - 1].push_back(end - 1);
		adj_l[end - 1].push_back(start - 1);
	}
	file_handler.close();
}

int* get_parents(list<int>* adj_l, const int v_num) {
	int* parent = new int[v_num];
	stack<int> stack;
	int v;
	parent[v_num - 1] = -1;
	stack.push(v_num - 1);
	while (!stack.empty()) {
		v = stack.top();
		stack.pop();
		for (auto to : adj_l[v]) {
			if (to != parent[v]) {
				parent[to] = v;
				stack.push(to);
			}
		}
	}
	return parent;
}

int* get_degrees(list<int>* adj_l, int v_num) {
	auto* degree = new int[v_num];
	for (auto i = 0; i < v_num; ++i) {
		degree[i] = adj_l[i].size();
	}
	return degree;
}

int get_pointer(int* degree, const int v_num, const int start_v) {
	for (auto i = start_v; i < v_num; ++i)
		if (degree[i] == 1)
			return i;
}

int* get_prufer_code(list<int>* adj_l , const int v_num)
{
	auto* prufer_code = new int[v_num - 2];
	auto* degree = get_degrees(adj_l, v_num);
	auto* parent = get_parents(adj_l, v_num);
	auto ptr = get_pointer(degree, v_num, 0);
	auto leaf = ptr;
	
	for (auto i = 0; i < v_num - 2; ++i) {
		int next = parent[leaf];
		prufer_code[i] = next + 1;
		--degree[next];
		if (degree[next] == 1 && next < ptr) {
			leaf = next;
		}
		else {
			ptr = get_pointer(degree, v_num, ++ptr);
			leaf = ptr;
		}
	}
	delete[] degree; delete[] parent;
	return prufer_code;
}

void print_array(int* arr, const int size) {
	for (auto i = 0; i < size; ++i)
		cout << arr[i] << " ";
	cout << '\n';
}

vector<int> convert_to_int(string str) {
	vector<int> arr_int;
	string temp;
	for (auto i = 0; i < str.length(); ++i) {
		if (str[i] == ' ') {
			regex_replace(temp, regex("^ +"), "");
			arr_int.push_back(stoi(temp) - 1);
			temp = "";
		}
		else temp += str[i];
	}
	arr_int.push_back(stoi(temp) - 1);
	return arr_int;
}

int* fill_array(const int size, const int filler) {
	auto* arr = new int[size];
	for (auto i = 0; i < size; ++i)
		arr[i] = filler;
	return arr;
}

int** fill_matrix(const int size, const int filler) {
	int** matrix = new int* [size];
	for (auto i = 0; i < size; ++i)
		matrix[i] = new int[size];
	for (auto i = 0; i < size; ++i)
		for (auto j = 0; j < size; ++j)
			matrix[i][j] = filler;
	return matrix;
}

string read_code(const char* file_name) {
	ifstream file_handler(file_name);
	string code;
	getline(file_handler, code);
	file_handler.close();
	return code;
}

int* degree_from_code(vector<int> prufer_code, int v_num) {
	auto* degree = fill_array(v_num, 1);
	for (auto i = 0; i < v_num - 2; ++i)
		++degree[prufer_code[i]];
	return degree;
}

int** decode_tree(vector<int> prufer_code) {
	auto const v_num = prufer_code.size() + 2;
	auto* degree = degree_from_code(prufer_code, v_num);
	int** adj_m = fill_matrix(v_num, 0);
	auto ptr = get_pointer(degree, v_num, 0);
	auto leaf = ptr;

	for (auto i = 0; i < v_num - 2; ++i) {
		int v = prufer_code[i];
		adj_m[leaf][v] = 1;
		adj_m[v][leaf] = 1;
		--degree[leaf];
		if (--degree[v] == 1 && v < ptr)
			leaf = v;
		else {
			ptr = get_pointer(degree, v_num, ++ptr);
			leaf = ptr;
		}
	}
	for (auto i = 0; i < v_num - 1; ++i) {
		if (degree[i] == 1)
			adj_m[i][v_num - 1] = 1;
	}
	delete[] degree;
	return adj_m;
}

void print_matrix(int** matrix, int size) {
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j)
			cout << setw(3) << matrix[i][j];
		cout << '\n';
	}
}

void show_menu() { 
	cout << "Choose one of the following : \n"
		 << "1 - find prufer code from tree\n"
		 << "2 - decode tree from prufer code\n";
}

void work_with_answer(int answer) {
	if (answer == 1) {
		list<int>* adj_l = nullptr;
		int v_num;
		get_input("input.txt", adj_l, v_num);
		auto* prufer_code = get_prufer_code(adj_l, v_num);
		cout << "Prufer code : \n";
		print_array(prufer_code, v_num - 2);
		delete[] prufer_code;
	}
	else {
		auto code = read_code("input.txt");
		auto int_code = convert_to_int(code);
		auto const v_num = int_code.size() + 2;
		auto** adj_m = decode_tree(int_code);
		cout << "Decoded adjancency matrix : \n";
		print_matrix(adj_m, v_num);
		delete_matrix(adj_m, v_num);
	}
}

void process_menu() {
	int answer = -1;
	show_menu();
	while (answer < 1 || answer > 2) {
		cout << "Type your choice : ";
		cin >> answer;
		cout << '\n';
	}
	work_with_answer(answer);
}

void delete_matrix(int** matrix, int row_size) {
	for (auto i = 0; i < row_size; ++i)
		delete[] matrix[i];
	delete[] matrix;
}

