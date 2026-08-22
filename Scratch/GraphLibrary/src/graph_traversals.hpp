#ifndef GRAPH_TRAVERSALS_HPP
#define GRAPH_TRAVERSALS_HPP



#include "graph.hpp"
#include <cinttypes>
#include <set>
#include <queue>
#include <stack>
#include <vector>

class GraphTraversals{
    public:
        // Runs breadth-first search algorithm on the graph.
        template<typename T> static std::vector<T> bfs(const Graph<T>& graph, const T& startNode){
            // result to be returned
            std::vector<T> traversed;

            // initialize visited set
            std::set<T> visitedSet;

            // initialize queue
            std::queue<T> que;

            //append start node to set and queue
            visitedSet.insert(startNode);
            que.push(startNode);

            // main algorithm
            while(!que.empty()){
                // pop from the queue and append to traversed
                T currNode = que.front(); // reads the value at the front of the queue
                // pops off items from queue but is void so returns nothing
                que.pop();
                traversed.push_back(currNode);

                // append neighboring nodes to the queue
                std::vector<T> nodeNeighbors = graph.getNeighbors(currNode);

                for(const auto& node: nodeNeighbors){
                    if(visitedSet.find(node) == visitedSet.end()){
                        que.push(node);
                        visitedSet.insert(node);
                    }
                }
            }
            return traversed;



        };
        // Runs depth-first search algorithm on the graph.
        template<typename T> static std::vector<T> dfs(const Graph<T>& graph, const T& startNode){
            // result to be returned
            std::vector<T> traversed;
            
            // initialize visited set
            std::set<T> visitedSet;

            // initialize stack
            std::stack<T> stck;

            //append start node to set and stack
            visitedSet.insert(startNode);
            stck.push(startNode);


            // main algorithm
            while(!stck.empty()){
                T currNode = stck.top();
                stck.pop();
                traversed.push_back(currNode);

                std::vector<T> nodeNeighbors = graph.getNeighbors(currNode);

                for(const auto& node: nodeNeighbors){
                    if(visitedSet.find(node) == visitedSet.end()){
                        stck.push(node);
                        visitedSet.insert(node);
                    }
                }

            }
            return traversed;
        };
};
#endif