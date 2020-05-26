# Modules
from math import hypot
from copy import copy
from math import ceil

# Const
INF = float('inf')


# Static methods
def get_input(file_name):
    with open(file_name, 'r') as file_handler:
        v_num = int(file_handler.readline())
        return [tuple(map(int, line.split())) for line in file_handler.readlines()]


# Calculate distance between points
def get_distance(p1, p2):
    return hypot(p1[0] - p2[0], p1[1] - p2[1])


# Get n order minimal element in array
def n_min(arr, n):
    return sorted(arr)[n - 1]


# Form adjacency matrix
def get_adj_matrix(points):
    v_num = len(points)
    adj_m = [[INF] * v_num for _ in range(v_num)]
    for i in range(v_num):
        for j in range(v_num):
            if i != j:
                adj_m[i][j] = get_distance(points[i], points[j])
    return adj_m


# Class for solving TSP problem
class Solver:
    def __init__(self, adj_m):
        self._adj_m = copy(adj_m)
        self._cost = INF
        self._v_num = len(adj_m)
        self._path = [-1] * (self._v_num + 1)
        self._visited = [False] * self._v_num

    # Save temporary solution
    def __copy_path(self, curr_path):
        self._path[:self._v_num + 1] = copy(curr_path)
        self._path[self._v_num] = curr_path[0]

    # Do main work
    def __TSPRecursive(self, curr_bound, curr_cost, level, curr_path):
        # Form answer on last level
        if level == self._v_num:
            curr_result = curr_cost + self._adj_m[curr_path[-1]][curr_path[0]]
            if curr_result < self._cost:
                self.__copy_path(curr_path)
                self._cost = curr_result
            return
        # Else form new tree on this level
        for i in range(self._v_num):
            if not self._visited[i]:
                temp_bound = curr_bound
                curr_cost += self._adj_m[curr_path[level - 1]][i]
                if level == 1:
                    curr_bound -= (n_min(self._adj_m[curr_path[0]], 1) + n_min(self._adj_m[i], 1)) / 2
                else:
                    curr_bound -= (n_min(self._adj_m[curr_path[0]], 2) + n_min(self._adj_m[i], 1)) / 2
                # If found new minimal
                if curr_bound + curr_cost < self._cost:
                    self._visited[i] = True
                    curr_path[level] = i
                    self.__TSPRecursive(curr_bound, curr_cost, level + 1, curr_path)
                # Else backtrack and reset all changes
                curr_cost -= self._adj_m[curr_path[level - 1]][i]
                curr_bound = temp_bound
                self._visited = [False] * self._v_num
                for index in range(self._v_num):
                    if curr_path[index] != -1:
                        self._visited[index] = True

    # Form answer
    def __TSP(self):
        curr_bound = 0
        curr_path = [-1] * (self._v_num + 1)
        visited = [False] * self._v_num

        for row in self._adj_m:
            curr_bound += n_min(row, 1) + n_min(row, 2)
        curr_bound = ceil(curr_bound / 2)
        self._visited[0] = True
        curr_path[0] = 0
        self.__TSPRecursive(curr_bound, 0, 1, curr_path)

    # Print formed result
    def print_result(self):
        self.__TSP()
        print(f'Minimal way cost is equal to {self._cost:.4f}')
        print('Current way :')
        for i in range(self._v_num + 1):
            print(self._path[i] + 1, end=' ')
            if i != self._v_num:
                print('-> ', end='')


# Main method
def main():
    points = get_input('input.txt')
    adj_m = get_adj_matrix(points)
    solver = Solver(adj_m)
    solver.print_result()


main()
