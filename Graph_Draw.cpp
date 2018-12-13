//
// Created by Maximilian Wiesmann on 13.12.2018.
// Outputs a TeX File that, compiled with LuaLaTeX, gives a graphical representation of a graph
//

#include<iostream>
#include<fstream>
#include<stdexcept>
#include "Graph.h"

void draw(const Graph & g){
    std::ofstream outputfile {"graph.tex"};
    if(outputfile.is_open()){
        outputfile << "\\documentclass{standalone}\n";
        outputfile << "\\usepackage{tikz}\n";
        outputfile << "\\usepackage{xcolor}\n";
        outputfile << "\\usetikzlibrary{graphdrawing, graphs}\n";
        outputfile << "\\usegdlibrary{force}\n";
        outputfile << "\\definecolor{dgreen}{rgb}{0.0, 0.42, 0.24}\n";
        outputfile << "\\begin{document}\n";
        outputfile << "\\tikz [spring layout] {\n";
        outputfile << "\\tikzstyle{every node}=[ball color=red,circle,text=white]\n";
        for(int i = 0; i < g.num_nodes(); ++i){
            outputfile << "\\node (" << i << ") {" << i << "};\n";
        }
        if(g.dirtype == Graph::undirected){
            for(int i = 0; i < g.num_nodes(); ++i){
                for(unsigned j = 0; j < g.get_node(i).adjacent_nodes().size(); ++j){
                    int adjacent_node_id = g.get_node(i).adjacent_nodes()[j].id();
                    outputfile << "\\draw (" << i << ") edge[--,dgreen] (" << adjacent_node_id << ");\n";
                }
            }
        }
        else if(g.dirtype == Graph::directed){
            for(int i = 0; i < g.num_nodes(); ++i){
                for(unsigned j = 0; j < g.get_node(i).adjacent_nodes().size(); ++j){
                    int adjacent_node_id = g.get_node(i).adjacent_nodes()[j].id();
                    outputfile << "\\draw (" << i << ") edge[->,dgreen] (" << adjacent_node_id << ");\n";
                }
            }
        }
        outputfile << "}\n";
        outputfile << "\\end{document}\n";
        outputfile.close();
    }
}

int main(){
    Graph g(6, Graph::undirected, Graph::random);
    draw(g);
    return 0;
}

