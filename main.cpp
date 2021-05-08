#include <iostream>
#include "Graph.h"
#include "FileToGraphParser.h"
#include "FordAlgo.h"

void printUsage(){
    std::cout << "Usage: FordAlgorithm <filename> <vertex1> <vertex2> <thread count>" << std::endl;
}


int main(int argc, char** argv) {

    if(argc != 5){
        printUsage();
        return 0;
    }
    Graph::Vid vertex1 = std::stoi(argv[2]);
    Graph::Vid vertex2 = std::stoi(argv[3]);
    num_threads = std::stoi(argv[4]);
    if(num_threads < 1 || num_threads > 12){
        std::cout << "Supported number of threads: from 1 to 12" << std::endl;
        return 0;
    }
    std::ifstream file;
    file.open(argv[1]);

    if(!file.is_open()){
        std::cout << "Could not open file: " << argv[1] << std::endl;
        std::cout << "No such file or directory" << std::endl;
        return 0;
    }

    Graph graph;
    if(!parseFile(file, graph)){
        std::cout << "Invalid input file" << std::endl;
        return 0;
    }

    file.close();

    if(graph.size() < 50) {
        std::cout << "Successfully read the graph: " << std::endl << graph << std::endl;
    }
    else{
        std::cout << "Graph has been read" << std::endl;
    }
    auto dists = fordAlgorithmJustDistance(vertex1, graph);
    std::cout << "Dist map for " << vertex1 << ": ";
    for(auto& dist: dists){
        std::cout << dist.first << "(" << dist.second << ") ";
    }

    std::cout << std::endl;

    auto path = fordAlgorithm(vertex1, vertex2, graph);

    std::cout << "Calculated path from " << vertex1 << " to " << vertex2 << " : ";
    bool first = true;
    for(auto it = path.begin(), end = path.end(); it != end; ++it) {
        if(!first) {
            auto prev = it;
            prev--;
            std::cout << "-(" << graph.getEdge(*(prev), *it).weight << ")-> ";
        }
        first = false;
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    return 0;
}
