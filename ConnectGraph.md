#Connect Graph

This algorithm runs BFS on the first vertex, marking every vertex it comes into contact with as discovered. Once the BFS queue is exhausted, if there are still undiscovered vertices the process repeats itself with the next undiscovered vertex. 

## Pseudocode
    int segments = -1
    for every vertex v in G:
        if not v.discovered:
            DFS(G, v) where BFS marks each vertex as discovered
            segments++
    return segments

## Proof of correctness
Beause BFS is a traversal it will touch on every node in a connected sub-graph. This means that the amount of BFS calls needed to discover every vertex is equal to the number of unique sub graphs. Therefore the amount of edges needed to connect them is that amount - 1

## Time estimate
BFS with an adjacency list - O(m+n)