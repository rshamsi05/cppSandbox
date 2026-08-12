#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>
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
  void add_vertex(const T &node) {
    /*
      check to see if vertex exists in the graph, if it does throw invalid
      argument exception.
    */
    if (has_vertex(node)) {
      throw std::invalid_argument("Vertex already exists in the graph!");
    }
    // add the vertex to the adjancey list
    adjList[node] = std::vector<T>();
  }
  // creates a edge between 2 existing nodes in the graph
  void add_edge(const T &node, const T &targetNode) {
    // check to see if both nodes exist in the graph
    if (!(has_vertex(node) && has_vertex(targetNode))) {
      throw std::invalid_argument(
          "One or both nodes do not exist in the graph");
    }
    // add connection betweeen node and target node
    adjList[node].push_back(targetNode);

    // for undirected graphs the connection should go both ways
    if (is_directed == false) {
      adjList[targetNode].push_back(node);
    }
  }
  // returns a list of all neighbors of the passed in node
  std::vector<T> getNeighbors(const T &node) const {
    // check to see if node exists in the graph
    if (!has_vertex(node)) {
      throw std::invalid_argument("Vertex does not exist in the graph!");
    }
    return adjList.at(node);
  }
  // checks to see if a vertex exists in the graph.
  bool has_vertex(const T &node) const {
    // not entirely to sure how this works
    return adjList.find(node) != adjList.end();
  }

  // graph attributes
private:
  std::unordered_map<T, std::vector<T>> adjList;
  bool is_directed;
};

#endif