#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

/*
- Template class that defines the structure of a graph
- Contains
    - adjaceny list
    - is_directed boolean attribute
*/

template <typename T> class Graph {

public:
  explicit Graph(bool directed = false)
      // member variables initialized in memory
      : is_directed(directed) {}

  // adds a vertex to the graph
  void add_vertex(const T &node) {}
  // creates a edge between 2 existing nodes in the graph
  void add_edge(const T &node, const T &targetNode) {}
  // returns a list of all neighbors of the passed in node
  std::vector<T> getNeighbors(const T &node) const {}
  // checks to see if a vertex exists in the graph.
  bool has_vertex(const T &node) const { return false; }

  // graph attributes
private:
  std::unordered_map<T, std::vector<T>> adjList;
  bool is_directed;
};

#endif