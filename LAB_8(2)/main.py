# Modules
from copy import copy

# Constants
INF = float('inf')

# Print MST
def print_min_tree(adj_m):
    to_print = process_prim(adj_m)
    if to_print is None:
          return print("Minimal spanning tree doesn't exist!")
    print("Minimal spanning tree: ")
    for row in to_print:
        for val in row:
            out_val = val if val != INF else '\u221e'
            print(f'{out_val:>5}', end = '')
        print()

# Prim algorithm    
def process_prim(adj_m):
    v_num = len(adj_m)
    used = [False] * v_num
    sel_edge = [-1] * v_num
    min_edge = [INF] * v_num
    mst = [[INF] * v_num for _ in range(v_num)]

    min_edge[0] = 0
    for i in range(v_num):
        v = -1
        # Find new start vertex
        for j in range(v_num):
            if not used[j] and (v == -1 or min_edge[j] < min_edge[v]):
                v = j
        # Check is possible to build MST
        if min_edge[v] == INF:
            return None
        # Build MST
        used[v] = True
        if sel_edge[v] != -1:
            mst[v][sel_edge[v]] = min_edge[v]
            mst[sel_edge[v]][v] = min_edge[v]
        # Try to find minimal edge from v
        for to in range(v_num):
            if adj_m[v][to] < min_edge[to]:
                min_edge[to] = adj_m[v][to]
                sel_edge[to] = v
    return mst
            
# Parse input file
def get_input(file_name):
    with open(file_name, "r") as file_handler:
        v_num, e_num = map(int, file_handler.readline().split())
        adj_m = [[INF] * v_num for _ in range(v_num)]
        for _ in range(e_num):
            start, end, weight = map(int, file_handler.readline().split())
            adj_m[start - 1][end - 1] = weight
            adj_m[end - 1][start - 1] = weight
    return adj_m

# Main method
def main():
    adj_m = get_input('input.txt')
    print_min_tree(adj_m)
    
main()
