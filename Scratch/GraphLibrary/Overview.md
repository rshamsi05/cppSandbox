# Creating a simple graph library from scratch


### Graph Class
- Want to be able to create a graph class that can mode both directed and undirected graphs
    - Not sure if creating 2 separate categories for the types of graphs is best or we can just use the same model for both types of graphs
    - Note: we should not have nodes in the graph with repeated values. (e.g 2 nodes cannot have the value james).
- How a graph class is initialized
    - a singular node is passed in to start the graph
- Basic functionality that can be used to expand the graph
    - add_vertex(node) -> takes the node and adds it to the current graph
    - add_edge(node, linkNode) -> binds the node with an existing linkNode in the graph
    - get_neighbors(node) -> performs and search and returns a list of all the neighboring nodes of the passed in node



### Graph Traversal Class
- Want to be able to run graph algorithms on the graphs we create and return a list of all the nodes that were visited in the order they were traveresed.
- bfs(graph, startVertex) -> returns list of all nodes in the graph that were visited in bfs order
- dfs(graph, startVertex) -> returns list of all nodes in the graph that were visited in dfs order



### Example usecase
```cpp
Graph<std::string> graph1; // creates a graph where the node types are just strings for this example but can be any type.
graph1.add_vertex("james"); // creates a node with the value of james and adds it to the graph
graph1.add_vertex("bob"); // creates a node with the value of bob and adds it to the graph
graph1.add_edge("james", "bob"); // creates an edge between james and bob in the graph
GraphTraversals.bfs(graph1, "james"); // returns a list of all nodes visited when performing bfs starting from node with james value.
```