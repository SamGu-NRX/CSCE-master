Guiding Q's
- How would one navigate a nodal network, such as rooms in a house
	- How can this be done in an efficient manner
- Imagine a game where states are represented by nodes, and edges represent moves
	- How can one find the optimal strategy for the game?

```
A = {B, C, E}
B = {G1}
C = {E, G2}
D = {A, B, E, G1}
E = {}
G1 = {}
G2 = {C, E}
```

Depth First Search (DFS)
- A
	- A -> B
		- A -> B -> G1
			- GO BACK
		- GO BACK
	- A -> C
		- A -> C -> E
			- GO BACK
		- A -> C -> G2
			- A -> C -> G2 -> E
				- GO BACK
			- GO BACK
		- GO BACK
	- A -> E
		- GO BACK

Breadth First Search (BFS)
- A (depth = 0)
	- A -> B (d = 1); Add {G1}
	- A -> C (d = 1); Add {E, G2}
	- A -> E (d = 1)
		- A -> B -> G1 (d = 2)
		- A -> C -> E (d = 2)
		- A -> C -> G2 (d = 2); Add {E}
			- A -> C -> G2 -> E (d = 3)

Complete Graph
- A graph wherein each node is connected to every other node
- Can be directed or undirected
	- (n+1) * n / 2 edges in undirected graph
	- n * n edges in directed graph

Clique
- A subset of nodes from a graph such that the subset forms a complete graph