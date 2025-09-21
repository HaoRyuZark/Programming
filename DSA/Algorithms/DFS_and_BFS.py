from collections import deque

class Vertex:
    def __init__(self, id: int) -> None:
        self.id = id 
        self.vertices = []
    
    def add_neighbor(self, n):
        self.vertices.append(n)

    def __hash__(self):
        return hash(self.id)

    def __eq__(self, other):
        return self.id == other.id

class Graph:
    def __init__(self, vertices: list[Vertex]) -> None:
        self.vertices = vertices

def reconstruct_path(fr: dict, last: Vertex) -> list[int]:

    path = []
    current = last
    while current is not None:
        path.append(current.id)
        current = fr.get(current)
    return path[::-1]

def bfs(graph: Graph, target_id: int) -> list[int]:
   
    start = graph.vertices[0]
    path = []
    visited = set()
    queue = deque()
    fr = {}

    queue.append(start)
    visited.add(start)
    fr[start] = None

    while queue:
   
        current = queue.popleft()

        if current.id == target_id:
            return reconstruct_path(fr, current)

        for neighbor in current.vertices:
       
            if neighbor not in visited:
           
                visited.add(neighbor)
                fr[neighbor] = current
                queue.append(neighbor)

    return []  # Return empty list if target_id not found

def bfs(graph: Graph, target_id: int) -> list[int]:
    
    start = graph.vertices[0]
    path = []
    visited = set()
    stack = []
    fr = {}

    stack.append(start)
    visited.add(start)
    fr[start] = None

    while stack:
   
        current = stack.pop()

        if current.id == target_id:
            return reconstruct_path(fr, current)

        for neighbor in current.vertices:
       
            if neighbor not in visited:
           
                visited.add(neighbor)
                fr[neighbor] = current
                stack.append(neighbor)

    return []  # Return empty list if target_id not found


