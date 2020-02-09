def parse_row(string):  # Фукнція, яка приводить вхідні дані до потрібного формату
    return tuple(map(int, string.split()))


def get_input(file_name):  # Зчитування вхідних даних з файлу
    edges_list = []
    with open(file_name, "r") as input_file:
        vertex, edges = parse_row(input_file.readline())
        data = input_file.readlines()
        for line in data:
            edges_list.append(parse_row(line))
    return vertex, edges, edges_list


def get_adjacency_matrix_nor(edges_list, vertex_num):  # Отримання матриці суміжності(неорієнтований)
    adj_matrix = [[0] * vertex_num for j in range(vertex_num)]
    for edge in edges_list:
        start, finish = edge[0] - 1, edge[1] - 1
        adj_matrix[start][finish] = 1
        adj_matrix[finish][start] = 1
    return adj_matrix


def get_adjacency_matrix(edges_list, vertex_num):  # Отримання матриці суміжності(орієнтований)
    adj_matrix = [[0] * vertex_num for j in range(vertex_num)]
    for edge in edges_list:
        start, finish = edge[0] - 1, edge[1] - 1
        adj_matrix[start][finish] = 1
    return adj_matrix


def get_incidence_matrix_nor(edges_list, vertex_num):  # Отримання матриці інцидентності(неорієнтований)
    inc_matrix = [[0] * len(edges_list) for j in range(vertex_num)]
    edge_number = 0
    for edge in edges_list:
        start, finish = edge[0] - 1, edge[1] - 1
        inc_matrix[start][edge_number] = 1
        inc_matrix[finish][edge_number] = 1
        edge_number += 1
    return inc_matrix


def get_incidence_matrix(edges_list, vertex_num):  # Отримання матриці інцидентності(орієнтований)
    inc_matrix = [[0] * len(edges_list) for j in range(vertex_num)]
    edge_number = 0
    for edge in edges_list:
        start, finish = edge[0] - 1, edge[1] - 1
        if start == finish:
            inc_matrix[start][edge_number] = 2
        else:
            inc_matrix[start][edge_number] = -1
            inc_matrix[finish][edge_number] = 1
        edge_number += 1
    return inc_matrix


def get_vertex_degree(adj_matrix):  # Отримання степеней кожної з вершин
    vertex_degrees = [0] * len(adj_matrix)
    for i in range(len(adj_matrix)):
        vertex_degrees[i] = sum(adj_matrix[i])
        if adj_matrix[i][i]:
            vertex_degrees[i] += 1
    return vertex_degrees


def get_half_in_degrees(inc_matrix):  # Отримання півстепенів заходу
    half_in_degrees = [0] * len(inc_matrix)
    counter = 0
    for row in inc_matrix:
        half_in_degrees[counter] = row.count(-1) + row.count(2)
        counter += 1
    return half_in_degrees


def get_half_out_degrees(inc_matrix):  # Отримання півстепенів виходу
    half_out_degrees = [0] * len(inc_matrix)
    counter = 0
    for row in inc_matrix:
        half_out_degrees[counter] = row.count(1) + row.count(2)
        counter += 1
    return half_out_degrees


def is_regular_nor(vertex_degrees):  # Перевірка на однорідність(неоднорідний)
    for number in vertex_degrees:
        if number != vertex_degrees[0]:
            return 0
    return 1


def is_regular(half_in, half_out):  # Перевірка на однорідність(однорідний)
    for i in range(len(half_in)):
        if  half_in[i] != half_in[0] or half_in[i] != half_out[0]:
            return 0
    return 1
    

def get_hanging_vertices(vertex_degrees):  # Отримання висячих вершин
    hanging_vertices = []
    for i in range(len(vertex_degrees)):
        if vertex_degrees[i] == 1:
            hanging_vertices.append(i)
    return hanging_vertices


def get_isolate_vertices(vertex_degrees):  # Отримання ізольованих вершин
    isolated_vertices = []
    for i in range(len(vertex_degrees)):
        if vertex_degrees[i] == 0:
            isolated_vertices.append(i)
    return isolated_vertices


def print_matrix(matrix):  # Вивід матриці в консоль
    for i in matrix:
        for j in i:
            print(j, end=" ")
        print()


def show_menu():  # Виводить меню в консоль
    print("Choose one of the following : ")
    print("""
             1 - show incidence matrix
             2 - show adjacency matrix
             3 - show degree of each vertex(only for non - directed graph)
             4 - show hanging and isolated vertices
             5 - show half - degrees or input and output(only for directed graph)
             6 - check graph for regulating
                                                        """)


def enter_number(graph_type):  # Перевірка коректності уведеного номеру
    answer = 0
    while answer < 1 or answer > 6:
        answer = int(input("Type the number : "))
        if answer < 1 or answer > 6:
            print("Invalid number!")
        if (graph_type == "directed" and answer == 3) or (graph_type == "non - directed" and answer == 5):
            print("Invalid number")
            answer = 0
            continue
    return answer


def work_with_number(graph_type, number):  # Опрацювання уведеного номеру
    n, m, edges_list = get_input("input.txt")
    if number == 1:
        if graph_type == "directed":
            print_matrix(get_incidence_matrix(edges_list, n))
        else:
            print_matrix(get_incidence_matrix_nor(edges_list, n))
    elif number == 2:
        if graph_type == "directed":
            print_matrix(get_adjacency_matrix(edges_list, n))
        else:
            print_matrix(get_adjacency_matrix_nor(edges_list, n))
    elif number == 3:
        print(*get_vertex_degree(get_adjacency_matrix_nor(edges_list, n)))
    elif number == 4:
        if graph_type == "directed":
            vertex_degrees = get_vertex_degree(get_adjacency_matrix(edges_list, n))
            print("Isolated vertices :", *get_isolate_vertices(vertex_degrees))
            print("Hanging vertices :", *get_hanging_vertices(vertex_degrees))
        else:
            vertex_degrees = get_vertex_degree(get_adjacency_matrix_nor(edges_list, n))
            print("Isolated vertices :", *get_isolate_vertices(vertex_degrees))
            print("Hanging vertices :", *get_hanging_vertices(vertex_degrees))
    elif number == 5:
        half_in = get_half_in_degrees(get_incidence_matrix(edges_list, n))
        half_out = get_half_out_degrees(get_incidence_matrix(edges_list, n))
        print("Half - degree of input : ", *half_in)
        print("Half - degree of output : ", *half_out)
    else:
        if graph_type == "directed":
            half_in = get_half_in_degrees(get_incidence_matrix(edges_list, n))
            half_out = get_half_out_degrees(get_incidence_matrix(edges_list, n))
            if is_regular(half_in, half_out):
                print("Graph is regular\nDegree of regular is equal to", half_in[0])
            else:
                print("Graph is not regular")
        else:
            vertex_degrees = get_vertex_degree(get_adjacency_matrix(edges_list, n))
            if is_regular_nor(vertex_degrees):
                print("Graph is regular\nDegree of regular is equal to", vertex_degrees[0])
                print("Graph is regular\nDegree of regular is equal to", vertex_degrees[0])
            else:
                print("Graph is not regular")


def start_menu():
    while True:
        graph_type = input("Enter a type of graph (directed / non - directed) : ")
        show_menu()
        answer = enter_number(graph_type)
        work_with_number(graph_type, answer)
        if input("Do you want to continue?(yes/no)").lower() == "no":
            break


start_menu()





