from copy import copy


class Graph:
    def __init__(self, n, m, edges_list):  # Constructor of graph
        self._n = n
        self._m = m
        self._edges_list = copy(edges_list)

    def __get_adjacency_matrix(self):
        pass

    def __get_incidence_matrix(self):
        pass

    def __enter_number(self):
        pass

    def __show_menu(self):
        pass

    def start_menu(self):
        pass

    def __work_with_number(self, number):
        pass


class NotDirectedGraph(Graph):

    def __get_vertex_degrees(self):  # Get degree of each vertex
        incidence_degree = [0] * self._n
        for start, finish in self._edges_list:
            incidence_degree[start - 1] += 1
            incidence_degree[finish - 1] += 1
        return incidence_degree

    def __get_isolated_vertices(self):  # Return isolated vertices
        vertex_degree = self.__get_vertex_degrees()
        isolated_vertices = []
        for i in range(len(vertex_degree)):
            if vertex_degree[i] == 0:
                isolated_vertices.append(i + 1)
        return isolated_vertices

    def __get_hanging_vertices(self):  # Return hanging vertices
        vertex_degree = self.__get_vertex_degrees()
        hanging_vertices = []
        for i in range(len(vertex_degree)):
            if vertex_degree[i] == 1:
                hanging_vertices.append(i + 1)
        return hanging_vertices

    def __get_adjacency_matrix(self):  # Return adjacency matrix
        adj_matrix = [[0 for i in range(self._n)] for j in range(self._n)]
        for start, finish in self._edges_list:
            adj_matrix[start - 1][finish - 1] = 1
            adj_matrix[finish - 1][start - 1] = 1
        return adj_matrix

    def __get_incidence_matrix(self):  # Return incidence matrix
        inc_matrix = [[0 for i in range(self._m)] for j in range(self._n)]
        edge_number = 0
        for edge in self._edges_list:
            start, finish = edge[0] - 1, edge[1] - 1
            inc_matrix[start][edge_number] = 1
            inc_matrix[finish][edge_number] = 1
            edge_number += 1
        return inc_matrix

    def __is_regular(self):  # Check graph for regulating
        vertex_degrees = self.__get_vertex_degrees()
        for value in vertex_degrees:
            if value != vertex_degrees[0]:
                return 0
        return 1

    def __get_regular_degree(self):  # Return regular degree
        vertex_degrees = self.__get_vertex_degrees()
        return vertex_degrees[0]

    def __enter_number(self):  # Enter and check number
        answer = 0
        while answer > 5 or answer < 1:
            answer = int(input("Type your choice : "))
            if answer > 5 or answer < 1:
                print("Invalid input!")
        return answer

    def __work_with_number(self, number):  # Process number
        if number == 1:
            print_matrix(self.__get_incidence_matrix())
        elif number == 2:
            print_matrix(self.__get_adjacency_matrix())
        elif number == 3:
            print(*self.__get_vertex_degrees())
        elif number == 4:
            hanging_vertices = self.__get_hanging_vertices()
            isolated_vertices = self.__get_isolated_vertices()
            if hanging_vertices:
                print("Hanging vertices :", *hanging_vertices)
            else:
                print("Graph does not have handle vertices!")
            if isolated_vertices:
                print("Isolated vertices :", *isolated_vertices)
            else:
                print("Graph does not have isolated vertices")
        elif number == 5:
            if self.__is_regular():
                print("Graph is regular!\nRegular degree is equal to", self.__get_regular_degree())
            else:
                print("Graph is not regular!")

    def __show_menu(self):  # Show menu
        print("Choose one of the following : ")
        print("""
             1 - show incidence matrix
             2 - show adjacency matrix
             3 - show degree of each vertex
             4 - show hanging and isolated vertices
             5 - check graph for regularity  """)

    def start_menu(self):  # Start work with graph
        self.__show_menu()
        self.__work_with_number(self.__enter_number())


class DirectedGraph(Graph):

    def __get_adjacency_matrix(self):  # Return adjacency matrix
        adj_matrix = [[0 for i in range(self._n)] for j in range(self._n)]
        for start, finish in self._edges_list:
            adj_matrix[start - 1][finish - 1] = 1
        return adj_matrix

    def __get_incidence_matrix(self):  # Return incidence matrix
        inc_matrix = [[0] * len(self._edges_list) for j in range(self._n)]
        edge_number = 0
        for edge in self._edges_list:
            start, finish = edge[0] - 1, edge[1] - 1
            if start == finish:
                inc_matrix[start][edge_number] = 2
            else:
                inc_matrix[start][edge_number] = -1
                inc_matrix[finish][edge_number] = 1
            edge_number += 1
        return inc_matrix

    def __get_half_in_degrees(self):  # Get in-degree of each vertex
        half_in_degrees = [0] * self._n
        for start, finish in self._edges_list:
            half_in_degrees[finish - 1] += 1
        return half_in_degrees

    def __get_half_out_degrees(self):  # Get out-degree of each vertex
        half_out_degrees = [0] * self._n
        for start, finish in self._edges_list:
            half_out_degrees[start - 1] += 1
        return half_out_degrees

    def __show_menu(self):  # Show menu
        print("Choose one of the following : ")
        print("""
                    1 - show incidence matrix
                    2 - show adjacency matrix
                    3 - show in-degrees and out-degrees of each vertex """)

    def __enter_number(self):  # Enter and check number
        answer = 0
        while answer > 3 or answer < 1:
            answer = int(input("Type your choice : "))
            if answer > 3 or answer < 1:
                print("Invalid input!")
        return answer

    def __work_with_number(self, number):  # Process number
        if number == 1:
            print_matrix(self.__get_incidence_matrix())
        elif number == 2:
            print_matrix(self.__get_adjacency_matrix())
        elif number == 3:
            print("In - degrees :", *self.__get_half_in_degrees())
            print("Out - degrees :", *self.__get_half_out_degrees())

    def start_menu(self):  # Start work with number
        self.__show_menu()
        self.__work_with_number(self.__enter_number())


def parse_row(string):  # Parse row of input data
    return tuple(map(int, string.split()))


def get_input(file_name):  # Get data from input file
    edges_list = []
    with open(file_name, "r") as input_file:
        vertex, edges = parse_row(input_file.readline())
        data = input_file.readlines()
        for line in data:
            if line != '\n':
                edges_list.append(parse_row(line))
    return vertex, edges, edges_list


def print_matrix(matrix):  # Print matrix
    for row in matrix:
        for i in row:
            print("{:>3}".format(i), end=" ")
        print()


def main():  # Start of program
    vertices_amount, edges_amount, edges_list = get_input("input.txt")
    while 1:
        type_of_graph = input("Is graph directed?(y/n) : ")
        if type_of_graph == "y":
            graph = DirectedGraph(vertices_amount, edges_amount, edges_list)
        else:
            graph = NotDirectedGraph(vertices_amount, edges_amount, edges_list)
        graph.start_menu()
        if input("If you want to exit type 'exit' else press any key...") == 'exit':
            break


main()
