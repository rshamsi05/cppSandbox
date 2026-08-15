#ifndef GRAPH_TRAVERSALS_HPP
#define GRAPH_TRAVERSALS_HPP



#include "graph.hpp"
#include <vector>

class GraphTraversals{
    public:
        // Runs breadth-first search algorithm on the graph.
        template<typename T> static std::vector<T> bfs(const Graph<T>& graph, const T& startNode){};
        // Runs depth-first search algorithm on the graph.
        template<typename T> static std::vector<T> dfs(const Graph<T>& graph, const T& startNode){};
};
#endif