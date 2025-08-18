'''
Only works for non cyclic directed graphs
'''
def topological_sort(graph) -> list[str]:

    visited = set()
    result = []
    
    for node in graph.adjacency_list:
        if node not in visited:
            dfs(node, visited, graph, result)

    
    return result[::-1]

def dfs(node, visited, graph, result):

    if node in visited:
        return

    visited.add(node)

    for neighbor in graph.adjacency_list.get(node):
        dfs(neighbor, visited, graph, result)

    result.append(node)



        
