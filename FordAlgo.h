//
// Created by Бушев Дмитрий on 09.05.2021.
//

#ifndef FORDALGORITHM_FORDALGO_H
#define FORDALGORITHM_FORDALGO_H
#include "Graph.h"
#include <list>

extern int num_threads;

std::list<Graph::Vid> fordAlgorithm(Graph::Vid s, Graph::Vid d, Graph const& graph);
std::map<Graph::Vid, Graph::Weight> fordAlgorithmJustDistance(Graph::Vid s, Graph const& graph);

#endif //FORDALGORITHM_FORDALGO_H
