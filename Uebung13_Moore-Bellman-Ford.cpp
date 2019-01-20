//
// Created by Maximilian Wiesmann on 20.01.2019.
//

#include "graph.h"
#include <vector>

struct PrevData {
    Graph::NodeId id;
    double weight;
};


Graph Moore_Bellman_Ford(const Graph & g, Graph::NodeId start_nodeid) {
    Graph tree(g.num_nodes(), g.dirtype);
    std::vector<double> values(g.num_nodes(), Graph::infinite_weight);
    std::vector<PrevData> prev(g.num_nodes(), {Graph::invalid_node, 0.0});

    values[start_nodeid] = 0;
    for (int i = 0; i < g.num_nodes(); ++i) {
        for (Graph::NodeId node = 0; node < g.num_nodes(); ++node) {
            for (auto neighbor : g.get_node(node).adjacent_nodes()) {
                if (values[node] + neighbor.edge_weight() < values[neighbor.id()]) {
                    values[neighbor.id()] = values[node] + neighbor.edge_weight();
                    prev[neighbor.id()] = {node, neighbor.edge_weight()};
                }
            }
        }
    }
    for (int i = 1; i < prev.size(); ++i) {
        if (prev[i].id != Graph::invalid_node) {
            tree.add_edge(prev[i].id, i, prev[i].weight);
        }
    }
    return tree;
}

int main(){
    Graph g("mbf_inst2", Graph::directed);
    //g.draw("graph.tex");
    Graph mbf_tree = Moore_Bellman_Ford(g, 0);
    //mbf_tree.draw("tree.tex");
}
