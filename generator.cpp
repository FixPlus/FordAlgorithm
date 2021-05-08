//
// Created by Бушев Дмитрий on 08.05.2021.
//

#include "Graph.h"
#include <iostream>
#include <fstream>
#include "GraphGenerator.h"

void printUsage(){
    std::cout << "Usage: Generator <filename> <vertex count> <sparsity(2 - 32)>" << std::endl;
}

int main(int argc, char** argv){
    if(argc != 4){
        printUsage();
        return 0;
    }
    Graph::Vid vertexCount = std::stoi(argv[2]);
    int sparsity = std::stoi(argv[3]);
    if(sparsity < 2 || sparsity > 32){
        std::cout << "Sparsity(arg 3) must be in bounds: [0, 32]" << std::endl;
        return 0;
    }

    Graph graph;

    generate(graph, vertexCount, sparsity);

    std::ofstream file;
    file.open(argv[1]);

    if(!file.is_open()){
        std::cout << "Could not open file: " << argv[1] << std::endl;
        std::cout << "No such file or directory" << std::endl;
        return 0;
    }

    file << graph;
    file.close();

    return 0;
}