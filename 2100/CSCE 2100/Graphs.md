Graphs can be modeled using sets. Let a graph G be defined as G = G(V, E). Therefore, V is the set of all vertices (nodes) and E is the set of all edges (relationship between two vertices).

Graphs can be either directed or undirected.

Directed Graph
- Set of tuples
	- ORDER MATTERS
- A set of nodes with a binary relation of A on N
- Ex. A --> B --> C <-->D
- Binary relation can be represented with arrows, matrices, etc.
```
0 1 0 0
0 0 1 0
0 0 0 1
0 0 1 0
```

- If some element X is directly preceding some element Y, we say that X is a direct predecessor of Y and Y is a direct successor of X
- If some element X is preceding (not necessarily directly) some element Y, we say that X is a predecessor of Y and Y is a successor of X

Undirected Graph
- Set of sets
	- ORDER DOES NOT MATTER
- No binary relation
- Ex. A -- B -- C -- D
- Avoid loops in undirected graphs
	- Hard to represent because sets must contain distinct values

Adjacency
- A two nodes are adjacent if they share an edge
	- 2 adjacent nodes are called neighbors

Degree (Undirected)
- The number of edges that connect to the node

In-Degree
- The number of edges that enter the node

Out-Degree
- The number of edges that exit the node

Total Degree
- The sum of the degrees of all nodes in a graph

Regularity
- Regular Graph: All nodes have the same degree
	- d-regular: All nodes have degree d

Graph Representation
- Diagram
	- Ex. [GRAPH]
- Adjacency List

```
1 -> 2, 3, 4
2 -> 3, 4
3 -> 1, 5
4 ->
5 -> 2, 5

We like to keep the list sorted, for efficiency during look-up
```

- Adjacency Matrix (array)

```
0 1 1 1 0
0 0 1 1 0
1 0 0 0 1
0 0 0 0 0
0 1 0 0 1
```

- Binary relation (digraphs) / set of sets (undirected graph)
	- Undirected:

```
connections = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 5}, {5}}
```

	- Directed

```
connections = {(1, 2), (1, 3), (1, 4), (2, 3), (2, 4), (3, 1), (3, 5), (5, 2), (5, 5)}
```

Undirected Weighted Graphs
- Graphs can be weighted
	- Facilitates ML, etc
- Representation of weighted graphs is also intuitive
	- Weights can be assigned to graph edges on diagram
	- Adjacency lists can have tuple (node, weight) instead of just node
	- Weights can be stored as value in the matrix instead of just 1
		- Non-zero value represents connection, 0 represents no connection

Directed Weighted Graphs
- Also intuitive to represent
	- Adjacency lists can have tuple (node, weight) instead of just node

Further Terminology

Walk
- List of alternating nodes and edges starting and ending with a node
- Can be open or closed
- Ex. < 1, (1, 2), 2, (2, 3), 3 >
	- Can be simplified to < 1, 2, 3 >
- | Walk | gives the cardinality of the walk
	- Number of nodes in walk

Open Walk
- Starting and ending nodes of the walk are not the same
- If no recurring edges, then Open Walk is a Trail

Closed Walk
- Starting and ending nodes of the walk are the same
- If no recurring edges, then Closed Walk is a Circuit

Trail
- If no recurring nodes, a trail is a Path

Circuit
- If no recurring nodes, a circuit is a Cycle

Path
- Length of a path with only a single node is 0 if no loop to itself, otherwise is 1

Cycle
- Contains at least 2 nodes in directed graph
- Contains at least 3 nodes in an undirected graph
- No defined "start"
	- Cycles are equivalent if the nodes have the same direct predecessors and direct successors

Acyclic
- A graph that contains no cycles
- 

Predecessor
- Direct Predecessor
	- Node directly before the target node
	- Ex. Given 1 --> 2, 1 is the direct predecessor of 2
- Indirect Predecessor
	- Node "after" the target node (following an edge)
	- Ex. Given 1 --> 2 --> 3, 1 is a predecessor of 3

Successor
- Direct Successor
	- Node directly after the target node
	- Ex. Given 1 --> 2, 2 is the direct successor of 1
- Indirect Successor
	- Node "after" the target node (following an edge)
	- Ex. Given 1 --> 2 --> 3, 3 is a successor of 1

