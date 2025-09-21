import heapq

def reconstruct_path(previous, distances, end) -> tuple[list[int], int]:
    
    path = []
    cost = distances[end]
    current = previous[end]

    while current:
        path.append(current)
        current = previous[current]

    return (path[::-1], cost)
        

def dijkstra(graph, start, end) ->  tuple[list[int], int]:
    
    path = []
    previous = {v: None for v in graph.adjacency_list}
    visited = {v: False for v in graph.adjacency_list}
    distances = {v: float('inf') for v in graph.adjacency_list} 

    priority_queue = []
    
    distances[start] = 0
    heapq.heappush(priority_queue, (start, 0))

    while priority_queue:
        
        current_weight, current_vertex = heapq.heappop(priority_queue)

        if current_vertex == end:
            return reconstruct_path(previous, distances, end)

        if visited[current_vertex]:
            continue 
         
        visited[current_vertex] = True 

        for v, w in graph.adjacency_list[current_vertex]:

            if visited[v]:
                continue 
            
            new_distance = current_weight + w

            if new_distance < distances[v]:
                
                previous[v] = current_vertex
                distances[v] = new_distance
                heapq.heappush(priority_queue, (v, new_distance))

    return ([], -1)
