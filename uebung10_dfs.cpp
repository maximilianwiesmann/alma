//
// Created by Maximilian Wiesmann on 11.12.2018.
//

#include <iostream>
#include <vector>
#include "Graph.h"

Graph dfs_rek(const Graph & graph, Graph::NodeId start_node, std::vector<bool> & visited, Graph & dfs_tree);

Graph dfs(const Graph & graph, Graph::NodeId start_node){
    std::vector<bool> visited(graph.num_nodes(), false);
    Graph dfs_tree(graph.num_nodes(), graph.dirtype);
    return dfs_rek(graph, start_node, visited, dfs_tree);
}

Graph dfs_rek(const Graph & graph, Graph::NodeId start_node, std::vector<bool> & visited, Graph & dfs_tree){
    visited[start_node] = true;
    std::vector<Graph::Neighbor> neighbors = graph.get_node(start_node).adjacent_nodes();
    for(unsigned i = 0; i < neighbors.size(); ++i){
        if(not visited[neighbors[i].id()]){
            visited[neighbors[i].id()] = true;
            dfs_tree.add_edge(start_node, neighbors[i].id());
            dfs_rek(graph, neighbors[i].id(), visited, dfs_tree);
        }
    }
    return dfs_tree;
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        Graph g(argv[1], Graph::undirected);
    //Graph g("sample_graph", Graph::undirected);
    //Graph g(7, Graph::undirected, Graph::random);
    Graph dfs_tree = dfs(g, 0);
    std::cout << "The following is a DFS-tree rooted at 0:\n";
    dfs_tree.print();
    }
}