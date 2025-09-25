'''
Only works for non cyclic directed graphs
'''

'''
Recursive version of dfs, can also be iterative
'''
def dfs(vertex: str, graph: dict[str, list[str]], visited: set[str], stack: list[str]):

    visited.add(vertex)

    for v in graph[vertex]:
        if v not in visited:
            dfs(v, graph, visited, stack)

    stack.append(vertex)

'''
Perform bfs on all vertecis and only once a the deepest neighbor is found put it on the stack.
Then reverse the order of the stack and return the order
'''
def topological_sort(graph) -> list[str]:

    visited = set()
    stack = []

    for vertex in graph:
        if vertex not in visited:
            dfs(vertex, graph, visited, stack)
    
    order = []
    while stack:
        order.append(stack.pop())
    
    return order


