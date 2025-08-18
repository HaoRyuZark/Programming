import heapq

# Java war mir zu viel Arbeit

class Graph:
    def __init__(self):
        self.adjacency_list = {}

    def add_edge(self, u, v, w):
        self.adjacency_list.setdefault(u, []).append((v, w))
        self.adjacency_list.setdefault(v, []).append((u, w)) 


def dijkstra(graph: Graph, start: str, end: str) -> list[str]:

    distances: dict[str, float] = {v: float('inf') for v in graph.adjacency_list}
    previous: dict[str, str] = {v: '' for v in graph.adjacency_list}
    visited: dict[str, bool] = {v: False for v in graph.adjacency_list}
    
    distances[start] = 0
    p_queue = [(0, start)]

    while p_queue:          # Relaxation
        
        current_distance, current_vertex = heapq.heappop(p_queue) # get vertex with the smallest distance

        if visited[current_vertex]:     # check if already visited
            continue
        
        visited[current_vertex] = True # if not set to visited

        for neighbor, weight in graph.adjacency_list[current_vertex]: # get all edges with discance of the current vertex 
            
            if visited[neighbor]: # check if visited
                continue

            new_distance = current_distance + weight # accumulative distance
            
            if new_distance < distances[neighbor]: # check if less
                
                distances[neighbor] = new_distance # update distance
                previous[neighbor] = current_vertex  # update 'from' 
                heapq.heappush(p_queue, (new_distance, neighbor)) # put vertex with new distance into the queue  

        
    
    # Reconstructing the path
    path = []
    current = end
    while current:
        path.append(current)
        current = previous[current]
    
    return path[::-1]



g = Graph()
g.add_edge('A', 'B', 1)
g.add_edge('B', 'C', 2)
g.add_edge('A', 'C', 4)
g.add_edge('C', 'D', 1)

path = dijkstra(g, 'A', 'D')
print("Shortest path from A to D:", path)


            


    
