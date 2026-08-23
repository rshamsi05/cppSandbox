#include "graph.hpp"
#include "graph_traversals.hpp"
#include <iostream>

int main() {
  Graph<std::string> graph1;
  graph1.add_vertex("john");
  graph1.add_vertex("joe");
  graph1.add_vertex("sean");
  graph1.add_vertex("bob");
  graph1.add_edge("john", "joe");
  graph1.add_edge("john", "sean");
  graph1.add_edge("joe", "bob");
  graph1.add_edge("sean", "bob");
  std::cout << "Johns neighbors: ";
  std::vector<std::string> johnNeighbors = graph1.getNeighbors("john");
  for(const auto& neighbor: johnNeighbors){
    std::cout << neighbor << ", ";
  }

  std::cout << std::endl;
  std::cout << "bfs on john: ";
  std::vector<std::string> bfsOnJohn = GraphTraversals::bfs<std::string>(graph1, "john");
  for(const auto& node: bfsOnJohn){
    std::cout << node << ", ";
  }


  std::cout << std::endl;
  std::cout << "dfs on john: ";
  std::vector<std::string> dfsOnJohn = GraphTraversals::dfs<std::string>(graph1, "john");
  for(const auto& node: dfsOnJohn){
    std::cout << node << ", ";
  }
  return 0;
}