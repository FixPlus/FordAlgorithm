//
// Created by Бушев Дмитрий on 09.05.2021.
//

#include "GraphGenerator.h"

void generate(Graph& graph, int vertCount, int sparsity){
    graph.clear();
    for(int i = 0; i < vertCount; ++i)
        graph.addVertex(i + 1);

    for(int i = 0; i < vertCount * vertCount / sparsity; ++i){
        Graph::Vid v1 = rand() % vertCount + 1;
        Graph::Vid v2 = rand() % vertCount + 1;
        int weight = rand() % 15 + 1;
        graph.addEdge(v1, v2, weight);
    }
}
