//
// Created by Бушев Дмитрий on 08.05.2021.
//
#include <ostream>
#include <algorithm>
#include "Graph.h"
void Graph::addVertex(Vid id){
    if(vertices.count(id) > 0){
        return;
    }
    else{
        vertices[id] = Vertex{};
    }
}

void Graph::addEdge(Vid from, Vid to, int weight){


    if(vertices.count(from) == 0)
        addVertex(from);
    if(vertices.count(to) == 0)
        addVertex(to);


    vertices.at(from).edges[to] = Weight{weight, false};
}

bool Graph::hasVertex(Graph::Vid vid) const{
    return vertices.count(vid) != 0;
}

Graph::Weight Graph::getEdge(Graph::Vid from, Graph::Vid to) const{
    auto& vertex = vertices.at(from);
    if(vertex.edges.count(to) == 0)
        return Weight{0, true};

    return vertex.edges.at(to);
}

std::ostream& operator<<(std::ostream& stream, Graph::Weight const& weight){
    if(weight.inf)
        stream << "inf";
    else
        stream << weight.weight;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, Graph const& graph){
    for(auto& vert: graph){
        stream << vert.first << ": ";
        for(auto& edge: vert.second.edges){
            stream << edge.first << " (" << edge.second << ") ";
        }
        stream << "; ";
    }
    return stream;
}
