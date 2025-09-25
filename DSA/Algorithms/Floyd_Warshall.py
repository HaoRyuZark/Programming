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
def floyd_warshall(graph: list[list[int]], distances: list[list[int]], pred: list[list[int]]):

    for vertex in range(0, len(graph)):

        for row in range(0, len(graph)):

            for col in range(0, len(graph)):

                new_dist = distances[row][vertex] + distances[vertex][col] 

                if new_dist < distances[row][col]:

                    distances[row][col] = new_dist
                    pred[row][col] = pred[vertex][col]


