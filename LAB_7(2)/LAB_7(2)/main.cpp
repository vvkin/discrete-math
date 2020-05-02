#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

struct two_parts {
	vector<int> first, second;
};

void get_input(const char*, list<int>*&, int&);
vector<int> get_bipartition(list<int>*, int);
two_parts get_two_parts(vector<int>);
vector<int*> get_matches(list<int>*, vector<int>);
void find_matches(vector<int*>&, list<int>*, vector<int>&, int&, int);
char** get_template_matrix(list<int>*, vector<int>, vector<int>);
void print_match(int*, vector<int>, vector<int>, char**);
void print_matrix(char**, int, int, vector<int>);
void print_matches(list<int>*,int);
void print_vector(vector<int>);

int main() {
	list<int>* adj_list = nullptr;
	int v_num;
	get_input("input.txt", adj_list, v_num);
	print_matches(adj_list, v_num);
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

vector<int> get_bipartition(list<int>* adj_l, int v_num) {
	vector<int> bipart(v_num, -1);
	queue<int> que;
	for (auto i = 0; i < v_num; ++i) {
		if (bipart[i] != -1 || adj_l[i].empty()) continue;
		que.push(i); bipart[i] = 0;
		while (!que.empty()) {
			int start = que.front();
			que.pop();
			for (auto v : adj_l[start]) {
				if (bipart[v] == -1) {
					bipart[v] = 1 - bipart[start];
					que.push(v);
				}
				else if (bipart[v] == bipart[start]) {
					return vector<int>();
				}
			}

		}
	}
	return bipart;
}

two_parts get_two_parts(vector<int> bipart) {
	two_parts res;
	for (auto i = 0; i < bipart.size(); ++i) {
		if (bipart[i]) res.first.push_back(i);
		else res.second.push_back(i);
	}
	if (res.second.size() < res.first.size())
		swap(res.second, res.first);
	return res;
}

void find_matches(vector<int*>& matching, list<int>* adj_l, vector<int>& l_part, int& to, int at) {
	for (auto& v : adj_l[l_part[at]]) {
		auto finded = false;
		for (auto i = 0; i < at; ++i) {
			if (matching[to][i] == v) {
				finded = true; break;
			}
		}
		if (finded) continue;
		matching[to][at] = v;
		if (at == l_part.size() - 1) {
			matching.push_back(new int[l_part.size()]);
			for (auto i = 0; i < l_part.size() - 1; ++i) {
				matching[to + 1][i] = matching[to][i];
			}
			++to; return;
		}
		find_matches(matching, adj_l, l_part, to, at + 1);
	}
	if (!at) matching.pop_back();
}

vector<int*> get_matches(list<int>* adj_l, vector<int> l_part) {
	vector<int*> matching{ new int[l_part.size()] };
	int to = 0;
	find_matches(matching, adj_l, l_part, to, 0);
	return matching;
}


char** get_template_matrix(list<int>* adj_l, vector<int> l_part, vector<int> r_part) {
	auto** t_matrix = new char*[/*l_part.size()*/ l_part.size() + r_part.size()];
	for (auto i = 0; i < l_part.size(); ++i) {
		t_matrix[i] = new char[/*r_part.size()*/ l_part.size() + r_part.size()];
	}
	for (auto i = 0; i < l_part.size(); ++i) {
		for (auto j = 0; j < r_part.size(); ++j) {
			t_matrix[i][j] = '*';
		}
	}
	for (auto src : l_part) {
		for (auto v : adj_l[src]) {
			t_matrix[src][v] = '0';
		}
	}
	return t_matrix;
}

void print_matrix(char** matrix, int row_num, int col_num, vector<int> l_part) {
	for (auto i = 0; i < row_num; ++i) {
		cout << setw(4) << l_part[i];
		for (auto j = 0; j < col_num; ++j) {
			cout << setw(4) << matrix[i][j];
		}
		cout << '\n';
	}
}

void print_vector(vector<int> vec) {
	for (auto el : vec) {
		cout << setw(4) << el;
	}
	cout << '\n';
}


void print_match(int* match, vector<int> l_part, vector<int> r_part, char** t_matrix) {
	print_vector(r_part);
	for (auto i = 0; i < l_part.size(); ++i) {
		t_matrix[l_part[i]][r_part[i]] = '1';
	}
	print_matrix(t_matrix, l_part.size(), r_part.size(), l_part);
}

void print_matches(list<int>* adj_l, int v_num) {
	auto bipart = get_bipartition(adj_l, v_num);
	if (bipart.size() == 0) {
		cout << "Graph is not biparted\n";
		return;
	}
	auto parts = get_two_parts(bipart);
	auto** t_matrix = get_template_matrix(adj_l, parts.first, parts.second);
	auto matching = get_matches(adj_l, parts.first);
	for (auto i = 0; i < matching.size(); ++i) {
		cout << "Matching " << i << " :\n";
		print_match(matching[i], parts.first, parts.second, t_matrix);
	}
}
