'''
Goal: Find the shortest path in a weighted graph

Limits: Does not work with negative edges, if they are necessary during the travering because of the remark.

Steps: 
    0. Set Cost of traveling to all nodes except for the star to infinity. (Initialize Single Source)
    1. Update stimates:  (Relax)
        Traverse all neighbors and update the neighbors stimates to their actual cost and update the visited path.
    2. Go to the node with the smallest cost.
    3. Repeat 1 and 2. Remember to add the time of traveling before reaching and only update if the estimate is minimal.
    
Remark:
    Each time we explore a new twon we garantee that we have the shortest path
'''

import heapq

class Graph:
    def __init__(self):
        self.adjacency_list = {}

    def add_edge(self, u, v, w):
        self.adjacency_list.setdefault(u, []).append((v, w))
        self.adjacency_list.setdefault(v, []).append((u, w)) 


def dijkstra_original(graph: Graph, start: str, end: str) -> list[str]:

    distances = {v: float('inf') for v in graph.adjacency_list}
    previous = {v: '' for v in graph.adjacency_list}
    visited = {v: False for v in graph.adjacency_list}
    
    distances[start] = 0
    p_queue = [(0, start)]

    while p_queue:
        
        current_distance, current_vertex = heapq.heappop(p_queue)

        if visited[current_vertex]:
            continue
        
        visited[current_vertex] = True

        for neighbor, weight in graph.adjacency_list[current_vertex]:
            
            if visited[neighbor]:
                continue

            new_distance = current_distance + weight
            
            if new_distance < distances[neighbor]:
                
                distances[neighbor] = new_distance
                previous[neighbor] = current_vertex
                heapq.heappush(p_queue, (new_distance, neighbor))   

        

    path = []
    current = end
    while current:
        path.append(current)
        current = previous[current]
    
    return path[::-1]


def dijkstra(n, edges, src):  # Basiclly a greedy bfs
    
    # Transform to adjacency list
    adj = {}
    for i in range(n):
        adj[i] = []

    for s, dst, weight in edges:
        adj[s].append([dst, weight])

    shortest = {}

    priority_queue = [[0, src]] # Step 0.
    
    # Perform search
    while priority_queue:

        current_weight, current = heapq.heappop(priority_queue) # Get first

        if current in shortest:             # If already visited continue
            continue

        shortest[current] = current_weight                                           # If not visited update estimate

        for node, weight in adj[current]:                                            # check neighbors
            
            if node not in shortest:                                                 # for neighbors
                heapq.heappush(priority_queue, [current_weight + weight, node])      # add neighbor to queue with the their estimate + currnt.

    # Outside the search
    # Add unvisited nodes and add negative distance
    for i in range(n):
        if i not in shortest:
            shortest[i] = -1

    return shortest

'''
Used for directed graphs

The Bellman Ford algorithm works with negative edges but not with negative clycles like dijkstra 

Note a path can have at most |v - 1| edges. If there are more then there is cycle because of repeated vertices.
'''
def bellman_ford(graph:Graph, start, end): 
 
    previous = {v: '' for v in graph.adjacency_list.keys()}
    distances = {v: float("inf") for v in graph.adjacency_list.keys()}
    
    distances[start] = 0
    num_vertices = len(graph.adjacency_list)
    
    # Relax all edges V-1 times
    for _ in range(num_vertices - 1):
        
        for u in graph.adjacency_list:
            
            for edge in graph.adjacency_list[u]:
                
                v = edge.vertex
                weight = edge.distance
                
                if distances[u] + weight < distances[v]:
                    
                    distances[v] = distances[u] + weight
                    previous[v] = u
        
    # Check again to detect negative cycles 
    for i in range(num_vertices - 1):
        
        for u in graph.adjacency_list:
            
            for edge in graph.adjacency_list[u]:
                
                v = edge.vertex
                weight = edge.distance
                
                if distances[u] + weight < distances[v]:
                    
                    distances[v] = float("inf")
            
    path = []
    current = end;

    if distances[end] == float("inf"):
        return None


    while current:

        path.append(current)
        current = previous = current

    path.reverse()

    return path
    
"""
Floyd-Warshall Algorithm — All-Pairs Shortest Paths

This algorithm computes the shortest paths between all pairs of nodes
in a weighted graph, including negative edge weights (but not negative cycles).

Use Case:
    - Solving all-pairs shortest path problems efficiently using dynamic programming.

Graph Representation:
    - The graph should be represented as an adjacency matrix.
    - Use float('inf') to represent the absence of a direct connection between nodes.

Predecessor Matrix:
    - A separate matrix is used to track the predecessors of each node in the shortest path.
    - Initially, for every edge (i, j) with a finite weight, set predecessor[i][j] = i.

Algorithm Steps:
    1. Initialize a distance matrix based on the input adjacency matrix.
    2. Initialize a predecessor matrix based on direct connections.
    3. For each node k (used as an intermediate node):
        - For each pair of nodes (i, j):
            - If going from i to j via k is shorter than the current known distance:
                - Update distance[i][j] = distance[i][k] + distance[k][j]
                - Update predecessor[i][j] = predecessor[k][j]

Edge Case Handling:
    - After all iterations, check if any diagonal entry in the distance matrix is negative.
    - A negative value on the diagonal indicates a negative cycle in the graph.

Example:
    Given:
        node = 1, row = 2, column = 4
        A[2][4] = ∞
        A[2][1] = 8
        A[1][4] = 7

    Since 8 + 7 < ∞, update:
        A[2][4] = 15
        P[2][4] = P[1][4]
"""

def floyd_warshall(adjacency_matrix):
    
    number_of_nodes = len(adjacency_matrix)
    
    dist = [row[:] for row in adjacency_matrix]
    pred = create_predecessor_matrix(dist, number_of_nodes)

    for k in range(number_of_nodes):
        for i in range(number_of_nodes):
            for j in range(number_of_nodes):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    pred[i][j] = pred[k][j]

    for i in range(number_of_nodes):
        if dist[i][i] < 0:
            print("Negative cycle!")
            return None, None

    return dist, pred

def create_predecessor_matrix(adjacency_matrix, number_of_nodes):
    
    temp = [[0 for _ in range(0, number_of_nodes)] for _ in range(0, number_of_nodes)] # Initialize with zeroes

    for row in range(0, number_of_nodes):

        for column in range(0, number_of_nodes):
            
            if adjacency_matrix[row][column] != float("inf"): # if there is a connection 
                adjacency_matrix[row][column] = row           # store the 


    return temp 

"""
Minimum Spanning Tree (MST) — Kruskal’s Algorithm

Problem:

    The Minimum Spanning Tree (MST) problem asks: 
    What is the most cost-effective way to connect all nodes in a weighted, undirected graph 
    such that all nodes are reachable and no cycles are formed?

    The goal is to find a subset of the edges that connects all vertices with the **minimum total weight**, 
    forming a spanning tree.

Use Cases:
    - Designing efficient computer networks
    - Laying out electrical grids or pipelines
    - Reducing infrastructure costs in transportation and communication networks

Kruskal's Algorithm (Greedy Approach):

    1. **Sort all edges** in ascending order based on weight.
    2. **Initialize a union-find (disjoint-set) structure** to track which components each node belongs to.
    3. Iterate through the sorted edges:
        - If the edge connects two nodes in **different components** (i.e., not forming a cycle),
          include it in the MST and unify their components.
        - If the edge connects two nodes **already in the same component**, skip it (it would form a cycle).
    4. Stop when exactly (n - 1) edges have been added to the MST (where n = number of nodes).

Why It Works (Greedy Justification):
    - This problem satisfies the **greedy-choice property** and **optimal substructure**.
    - At each step, the algorithm selects the **minimum-weight edge** that maintains a valid tree structure.
    - If we skipped the smallest available edge, we would eventually need to use a higher-weight edge to 
      complete the tree — which would contradict the goal of minimizing total weight.
    - Skipping a valid edge might also lead us to revisit it later, potentially forming a cycle — 
      which Kruskal's algorithm avoids.

Note:
    - Kruskal’s algorithm is efficient and works well with sparse graphs.
    - For dense graphs, **Prim’s algorithm** may be more efficient depending on the implementation.

"""

class DisjointSet:

    def __init__(self, vertices):
        self.parent = {v: v for v in vertices} # init with separate sets
        self.rank = {v: 0 for v in vertices}  # set ranks to 0

    def find(self, v): # find representant
        
        if self.parent[v] != v:
            self.parent[v] = self.find(self.parent[v])  # Path compression
        
        return self.parent[v]

    def union(self, u, v):

        root_u = self.find(u)
        root_v = self.find(v)

        if root_u == root_v:
            return False  # Cycle detected

        # Union by rank: The one with the lower rank becomes child
        if self.rank[root_u] < self.rank[root_v]:
            
            self.parent[root_u] = root_v

        elif self.rank[root_u] > self.rank[root_v]:
            
            self.parent[root_v] = root_u
        
        else:
        
            self.parent[root_v] = root_u
            self.rank[root_u] += 1

        return True


def kruskal(vertices, edges):

    # Sort edges by weight
    edges.sort(key=lambda x: x[2])
    ds = DisjointSet(vertices) # Initialize set of disjoint sets

    mst = []
    total_weight = 0

    for u, v, weight in edges: # iterate over the edges
        
        if ds.union(u, v):              # Unify
            mst.append((u, v, weight))  # add if union was succesfull
            total_weight += weight      # augment total_weight

    return mst, total_weight


# Example usage
vertices = ['A', 'B', 'C', 'D', 'E']
edges = [
    ('A', 'B', 1),
    ('A', 'C', 3),
    ('B', 'C', 1),
    ('B', 'D', 6),
    ('C', 'D', 4),
    ('C', 'E', 2),
    ('D', 'E', 5)
]

mst, total_weight = kruskal(vertices, edges)
print("Minimum Spanning Tree:", mst)
print("Total Weight:", total_weight)
 

"""
Prim’s Algorithm — Minimum Spanning Tree (MST)

Problem:
    - Given a connected, undirected, weighted graph, Prim’s algorithm finds the subset of edges 
      that form a tree including all vertices, such that the total weight of all the edges is minimized.
    - Unlike Kruskal's algorithm, Prim’s algorithm grows the MST **starting from a single node** 
      and expanding one edge at a time.

Use Cases:
    - Designing minimal-cost infrastructure (e.g., fiber optic layouts, roads, pipelines)
    - Real-time applications where dynamic graph exploration is needed

Algorithm Overview:
    1. Start from an arbitrary node (often node 0).
    2. Use a **priority queue (min-heap)** to always select the edge with the smallest weight 
       that connects a visited node to an unvisited node.
    3. Mark the chosen node as visited and add the edge to the MST.
    4. Push all edges from this new node to unvisited neighbors into the priority queue.
    5. Repeat until all nodes have been visited (i.e., MST contains exactly n - 1 edges).

Key Concepts:
    - Prim’s algorithm is a **greedy algorithm**: at each step, it chooses the cheapest edge available 
      that maintains tree structure (i.e., no cycles).
    - It is especially efficient for **dense graphs** using a min-priority queue (e.g., a heap).
    - To efficiently check for visited nodes, a boolean array or a set is commonly used.

Greedy Justification:
    - Like Kruskal’s, Prim’s algorithm relies on the **greedy-choice property** and **optimal substructure**.
    - It guarantees that at each stage, the local optimal choice (cheapest valid edge) leads to a globally optimal solution.

Comparison with Kruskal’s Algorithm:
    - **Prim’s** grows the MST **from a starting node**, using local edge information.
    - **Kruskal’s** builds the MST by **globally sorting all edges**, then picking non-cycling ones.
    - Prim’s is typically more efficient on dense graphs, while Kruskal’s is better for sparse graphs.

"""
def prim(graph, start):
    mst = []
    visited = set()
    min_heap = [(0, start, None)]  # (weight, current_node, parent)
    total_weight = 0

    while min_heap:
        weight, current, parent = heapq.heappop(min_heap)

        if current in visited:
            continue

        visited.add(current)
        if parent is not None:
            mst.append((parent, current, weight))
            total_weight += weight

        for neighbor, edge_weight in graph[current]:
            if neighbor not in visited:
                heapq.heappush(min_heap, (edge_weight, neighbor, current))

    return mst, total_weight

from collections import defaultdict
# Example usage
graph = defaultdict(list)
edges = [
    ('A', 'B', 1),
    ('A', 'C', 3),
    ('B', 'C', 1),
    ('B', 'D', 6),
    ('C', 'D', 4),
    ('C', 'E', 2),
    ('D', 'E', 5)
]

# Build adjacency list
for u, v, w in edges:
    graph[u].append((v, w))
    graph[v].append((u, w))

mst, total_weight = prim(graph, 'A')
print("Minimum Spanning Tree:", mst)
print("Total Weight:", total_weight)


"""
Maximum Flow — Ford-Fulkerson Algorithm

Maximum Flow Problem:
    - Given a flow network (a directed graph where each edge has a capacity), determine the 
      maximum amount of flow that can be sent from a designated source node to a sink node.
    - Each edge has a limited capacity, and the total flow through it cannot exceed this limit.

Key Concepts:

    - **Augmenting Path**:
        A path from the source (s) to the sink (t) in the residual graph where each edge has 
        remaining capacity > 0.

    - **Bottleneck Capacity**:
        The smallest remaining capacity along an augmenting path. It determines the maximum 
        amount of flow that can be sent along that path.

    - **Augmenting the Flow**:
        Increase the flow along each edge in the augmenting path by the bottleneck value.
        - In forward edges: add the bottleneck.
        - In backward (residual) edges: subtract the bottleneck.
        This allows for "undoing" flow along previous paths if a better path is found.

    - **Residual Graph**:
        - Built from the original graph by representing available capacity for sending more flow.
        - Includes both forward edges (capacity - flow) and backward edges (flow).
        - Allows us to reverse flow if a previous path choice is suboptimal.
        - Critical: Optimization happens in the residual graph, not the original one.

    - **Remaining Capacity**:
        Defined as: `remaining = capacity - flow`
        Residual edges exist with flow values to represent "how much was pushed" and allow 
        rollback if necessary.

    - **Minimum Cut**:
        - A cut partitions the graph into two disjoint sets, separating the source and sink.
        - The minimum cut is the smallest total capacity of edges that, if removed, would disconnect
          the source from the sink.
        - By the Max-Flow Min-Cut Theorem, the value of the maximum flow equals the capacity of the minimum cut.

Matching:
    - A **matching** in a graph G = (V, E) is a subset of edges with no shared endpoints.
    - Matching problems (like in bipartite graphs) can be reduced to maximum flow problems by:
        - Adding a source node connected to one partition,
        - Adding a sink node connected to the other,
        - Assigning unit capacities (usually 1) to the edges.

Ford-Fulkerson Algorithm Steps:
    1. While an augmenting path exists from the source to the sink:
        a. Find the path (can use BFS or DFS).
        b. Determine the bottleneck capacity.
        c. Augment the flow along the path.
    2. Repeat until no more augmenting paths are found.

Notes:
    - Backward (residual) edges are essential for reversing poor flow decisions.
    - Drawing the graph twice (once with capacities, once with current flows/residuals)
      can aid in understanding flow state during execution.
    - The algorithm is not guaranteed to terminate on irrational capacities unless the
      capacities are integers (in which case it’s guaranteed to converge).

Use Cases:
    - Network flow optimization
    - Bipartite graph matching
    - Circulation and routing problems
    - Job assignment problems
"""
def bfs(source, sink, parent):
    pass

def ford_fulkerson(graph, source, sink):
    
    max_flow = 0
    parent = [-1]  # array of the for the paths

    while bfs(source, sink, parent):  # iterate as long there are paths

        # Setup for going backwards
        path_flow = float("inf")
        s = sink
        
        #Find minimum residual capacity along the path found by bfs
        while s != source:
            path_flow = min(path_flow, graph[parent[s]][s])
            s = parent[s]

        # adding path flow to the generall flow
        max_flow += path_flow
        
        # Update residual capcities of the edges and reverse edges
        v = sink

        while v != source:
            u = parent[v]
            graph[u][v] -= path_flow
            graph[v][u] += path_flow
            v = parent[v]

        return max_flow


"""
Traveling Salesman Problem (TSP)

Overview:
    - The Traveling Salesman Problem asks: "Given a list of cities and the distances between each pair,
      what is the shortest possible route that visits each city exactly once and returns to the starting point?"
    - This is a classic **NP-hard** combinatorial optimization problem.
    - A solution to TSP is a **Hamiltonian cycle** with minimal total cost in a complete, weighted graph.

Key Definitions:

    - **Hamiltonian Path**: A path that visits every vertex in the graph exactly once.
    - **Traceable Graph**: A graph that contains a Hamiltonian path.
    - **Hamiltonian Cycle**: A closed Hamiltonian path — it visits every vertex exactly once and returns to the starting point.
    - **Hamiltonian Graph**: A graph that contains a Hamiltonian cycle.
    - **Simple Graph**: A graph in which no two vertices are connected by more than one edge (no parallel edges or loops).
    - **Dirac's Theorem**:
        For a simple graph with n ≥ 3 vertices: If every vertex has degree ≥ n/2,
        the graph contains a Hamiltonian cycle.
    - **Ore's Theorem**:
        For a simple graph with n ≥ 3 vertices: If for every pair of non-adjacent vertices (u, v),
        deg(u) + deg(v) ≥ n, then the graph contains a Hamiltonian cycle.

Comparison with Eulerian Paths:
    - **Eulerian Trail**: A walk that uses every edge exactly once (may be open or closed).
    - **Eulerian Circuit**: A trail that uses every edge exactly once and returns to the starting vertex.
    - Note: Eulerian paths focus on *edges*, Hamiltonian paths focus on *vertices*.

Lower Bounds:
    - The cost of a **Minimum Spanning Tree (MST)** of the graph is a common lower bound for the optimal TSP solution.

Approximation Algorithms (for Metric TSP):

    - **Nearest Neighbor Heuristic**:
        - Start at any node.
        - At each step, travel to the nearest unvisited node.
        - Return to the starting point after visiting all nodes.
        - Simple, but often far from optimal.

    - **MST-DFS Method (2-Approximation)**:
        1. Construct a complete graph (if needed).
        2. Compute the MST using Kruskal’s or Prim’s algorithm.
        3. Perform a DFS traversal of the MST.
        4. Shortcut duplicate visits (i.e., remove repeated vertices in traversal order).
        5. Return to the start to complete the cycle.
        - Guarantees a path within 2× the optimal cost (metric TSP only).

    - **Christofides’ Algorithm (1.5-Approximation)**:
        1. Build the MST of the graph.
        2. Let O be the set of vertices in the MST with odd degree.
        3. Find a **minimum-cost perfect matching** M among the vertices in O.
        4. Combine the MST and matching M to create a multigraph with all even degrees.
        5. Find an Eulerian circuit in this multigraph.
        6. Shortcut repeated vertices to obtain a Hamiltonian cycle.
        - Applicable to **metric TSP** (where triangle inequality holds).
        - Offers a provable approximation ratio of 1.5× the optimal cost.

"""
def tsp(graph):
    pass

def main():

    g = Graph()
    g.add_edge("A", "B", 1)
    g.add_edge("B", "C", 2)
    g.add_edge("A", "C", 4)

    print(bellman_ford(g, "A", "C"))  # Output: ['A', 'B', 'C']

                     
main()
