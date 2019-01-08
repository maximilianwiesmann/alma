//
// Created by Jonas Lippert and Maximilian Wiesmann on 08.01.2019.
//

#include <iostream>
#include <vector>
#include "graph.h"
#include "queue.h"

bool test_tree(Graph &graph){
    int num_nodes = graph.num_nodes();
    int num_edges = 0;
    for(auto i = 0; i < num_nodes; ++i){
        num_edges += graph.get_node(i).adjacent_nodes().size();
    }
    if(graph.dirtype == Graph::undirected)
        num_edges /= 2;
    if(num_nodes != num_edges + 1) {      //ueberpruefe richtige Kantenanzahl
        return false;
    }
    int start_node = -1;
    if(graph.dirtype == Graph::undirected)
        start_node = 0;
    else{
        std::vector<bool> possible_start_nodes(graph.num_nodes(), true);        //ueberpruefe, ob es Startknoten fuer Durchmusterung gibt
        for(auto i = 0; i < graph.num_nodes(); ++i){
            for(unsigned j = 0; j < graph.get_node(i).adjacent_nodes().size(); ++j){
                possible_start_nodes[graph.get_node(i).adjacent_nodes()[j].id()] = false;
            }
        }
        for(unsigned i = 0; i < possible_start_nodes.size(); ++i){
            if(possible_start_nodes[i]){
                start_node = i;
                break;
            }
        }
        if(start_node == -1)
            return false;
    }
    int num_visited_nodes = 1;
    std::vector<bool> visited(graph.num_nodes(), false);        //Durchmusterung
    Queue<Graph::NodeId> queue;
    queue.push_back(start_node);
    visited[start_node] = true;
    while (not queue.is_empty()) {
        auto cur_nodeid = queue.pop_front();
        for (auto neighbor: graph.get_node(cur_nodeid).adjacent_nodes()) {
            if (not visited[neighbor.id()]) {
                visited[neighbor.id()] = true;
                ++num_visited_nodes;
                queue.push_back(neighbor.id());
            }
        }
    }
    return (num_nodes == num_visited_nodes);
}

Graph bfs(const Graph & graph, Graph::NodeId start_node)
{
    std::vector<bool> visited(graph.num_nodes(), false);
    std::vector<int> dist(graph.num_nodes(), -1);
    Graph bfs_tree(graph.num_nodes(), graph.dirtype);
    Queue<Graph::NodeId> queue;
    queue.push_back(start_node);
    visited[start_node] = true;
    dist[start_node] = 0;

    while (not queue.is_empty()) {
        auto cur_nodeid = queue.pop_front();
        for (auto neighbor: graph.get_node(cur_nodeid).adjacent_nodes()) {
            if (not visited[neighbor.id()]) {
                visited[neighbor.id()] = true;
                dist[neighbor.id()] = dist[cur_nodeid] + 1;
                bfs_tree.add_edge(cur_nodeid, neighbor.id());
                queue.push_back(neighbor.id());
            }
        }
    }

    return bfs_tree;
}

int main(){
    Graph g(10, Graph::directed, Graph::random);
    Graph tree = bfs(g, 0);
    tree.draw("tree.tex");
    if(test_tree(tree))
        std::cout << "Baum" << std::endl;
    else
        std::cout << "kein Baum" << std::endl;
    return 0;
}