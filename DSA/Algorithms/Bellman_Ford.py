"""
Used for directed graphs

The Bellman Ford algorithm works with negative edges but not with negative clycles like dijkstra 

Note a path can have at most |v - 1| edges. If there are more then there is cycle because of 
repeated vertices. Therefore, we only relax | v - 1| times
"""
def bellman_ford(graph: dict[str, list[tuple[str, int]]], start: str):
    
    distances = {v: float("inf") for v in graph}
    predecessors = {v: "" for v in graph}
    
    distances[start] = 0

    for _ in range(len(graph) - 1):
        for u in graph:
            for v, weight in graph[u]:
                if distances[u] + weight < distances[v]:
                    distances[v] = distances[u] + weight
                    predecessors[v] = u

    for u in graph:
        for v, weight in graph[u]:
            if distances[u] + weight < distances[v]:
                raise ValueError("Graph contains a negative-weight cycle")

    return distances, predecessors
