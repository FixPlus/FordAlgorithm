//
// Created by Бушев Дмитрий on 09.05.2021.
//
#include "GraphGenerator.h"
#include "FordAlgo.h"
#include <iostream>
#include <chrono>

void printUsage(){
    std::cout << "Usage: PerfChecker <thread count[1, 12]> <max graph size[1, 32]> <sparsity[1, 32]>" << std::endl;
}

int main(int argc, char** argv){

    if(argc != 4){
        printUsage();
        return 0;
    }
    int maxN, sparsity;

    num_threads = std::stoi(argv[1]);
    maxN = std::stoi(argv[2]);
    sparsity = std::stoi(argv[3]);

    if(num_threads < 1 || num_threads > 12){
        std::cout << "Wrong thread count" << std::endl;
        printUsage();
        return 0;
    }

    if(maxN < 1 || maxN > 32){
        std::cout << "Wrong max graph size" << std::endl;
        printUsage();
        return 0;
    }

    if(sparsity < 1 || sparsity > 32){
        std::cout << "Wrong sparsity" << std::endl;
        printUsage();
        return 0;
    }

    int graphSize = 2;

    std::cout << "Initialize tests with " << num_threads << " threads active, sparsity of all graphs = " << sparsity
        << std::endl;
    Graph::Vid s = 1;

    std::vector<std::pair<int, double>> results;

    for(int i = 0; i < maxN; i++){
        Graph graph;

        std::cout << "Vertex count " << graphSize << " graph in calculation...";

        generate(graph, graphSize, sparsity);

        auto tStart = std::chrono::high_resolution_clock::now();

        auto dists = fordAlgorithmJustDistance(s, graph);

        auto tEnd = std::chrono::high_resolution_clock::now();
        auto frameTime = std::chrono::duration<double, std::milli>(tEnd - tStart).count();

        results.emplace_back(graphSize, frameTime);

        std::cout << "Done! Time elapsed: " << frameTime << "ms" << std::endl;

        std::cout << "Dist map for " << s << ": ";
        for(auto& dist: dists){
            std::cout << dist.first << "(" << dist.second << ") ";
        }
        std::cout << std::endl << std::endl;

        graphSize <<= 1u;
    }

    std::cout << "Perf check finished. results:" << std::endl;
    std::cout << "Vertex count : time elapsed" << std::endl;

    for(auto& res: results){
        std::cout << res.first << " : " << res.second << "ms" << std::endl;
    }

    return 0;

}