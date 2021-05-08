//
// Created by Бушев Дмитрий on 09.05.2021.
//

#include "FordAlgo.h"
#include <iostream>
#include <thread>
#include <mutex>

int num_threads = 12;

std::mutex sync_mutex;
std::mutex calc_mutex;
std::map<Graph::Vid, Graph::Vertex>::const_iterator nextToGo;


void fordAlgorithmSubRoutineWithPMat(Graph const& graph, Graph::Vid vert, std::map<Graph::Vid, Graph::Weight> const& prevMap, std::map<Graph::Vid, Graph::Weight>& curMap, std::map<Graph::Vid, Graph::Vid>& curP){
    while(true) {
        auto v1_dist = prevMap.at(vert);
        auto &weightToCalc = curMap.at(vert);
        auto &prevToCalc = curP.at(vert);


        if(v1_dist != 0)
            for (auto const& v2: prevMap) {
                auto vert2 = v2.first;
                if (vert == vert2)
                    continue;
                auto v2_dist = v2.second;
                if (v2_dist.inf)
                    continue;

                auto edge_weight = graph.getEdge(vert2, vert);

                if (edge_weight.inf)
                    continue;

                if (v1_dist.inf || edge_weight + v2_dist < v1_dist) {
                    weightToCalc = edge_weight + v2_dist;
                    v1_dist = weightToCalc;
                    prevToCalc = vert2;
                }
                if (weightToCalc == 0)
                    break;
            }

        sync_mutex.lock();
        if (nextToGo != graph.end()) {
            vert = (*nextToGo).first;

            nextToGo++;
        }
        else{
            sync_mutex.unlock();
            break;
        }
        sync_mutex.unlock();
    }
}

std::list<Graph::Vid> fordAlgorithm(Graph::Vid s, Graph::Vid d, Graph const& graph){
    calc_mutex.lock();
    std::vector<std::map<Graph::Vid, Graph::Weight>> matA;
    std::vector<std::map<Graph::Vid, Graph::Vid>> matP;

    matA.resize(graph.size());
    matP.resize(graph.size());

    for(auto& vertex: graph) {
        bool first = true;
        for (auto &map: matA) {
            map[vertex.first] = vertex.first == s && first ? 0 : Graph::Weight{0, true};
            first = false;
        }
        first = true;
        for (auto &map: matP) {
            map[vertex.first] = (vertex.first == s && first) ? vertex.first : -1;
            first = false;
        }
    }

    int active_threads = num_threads < graph.size() ? num_threads : graph.size();

    for(int i = 1, sz = graph.size(); i < sz; ++i){

        std::vector<std::thread> threads;
        threads.reserve(active_threads);

        nextToGo = graph.begin();

        for(int j = 0; j < active_threads; ++j, ++nextToGo);

        auto it = graph.begin();

        for(int j = 0; j < active_threads; ++j, ++it)
            threads.emplace_back(fordAlgorithmSubRoutineWithPMat, std::ref(graph), (*it).first, std::ref(matA.at(i - 1)), std::ref(matA.at(i)), std::ref(matP.at(i)));

        for(auto& thread: threads)
            thread.join();
    }
    calc_mutex.unlock();

    int minDistStepCount = -1;
    int minDist = 0;

    for(int i = 0; i < graph.size(); ++i) {
        auto dist = matA.at(i).at(d);
        if (!dist.inf && (minDistStepCount == -1 || dist < minDist)) {
            minDistStepCount = i;
            minDist = dist.weight;
        }
    }
    std::list<Graph::Vid> path;

    if(minDistStepCount == -1){
        std::cout << "no path" << std::endl;
        return path;
    }

    std::cout << minDistStepCount << " "<< minDist << std::endl;

    path.push_front(d);

    while(minDistStepCount > 0 && d != s){
        d = matP.at(minDistStepCount).at(d);
        path.push_front(d);
        minDistStepCount--;
    }
    return path;
}


void fordAlgorithmSubRoutine(Graph const& graph, Graph::Vid vert, std::map<Graph::Vid, Graph::Weight> const& prevMap, std::map<Graph::Vid, Graph::Weight>& curMap){
    while(true) {
        auto v1_dist = prevMap.at(vert);
        auto &weightToCalc = curMap.at(vert);
        weightToCalc = v1_dist;

        if (v1_dist != 0)
            for (auto const& v2: prevMap) {
                auto vert2 = v2.first;
                if (vert == vert2)
                    continue;
                auto v2_dist = prevMap.at(vert2);
                if (v2_dist.inf)
                    continue;

                auto edge_weight = graph.getEdge(vert2, vert);

                if (edge_weight.inf)
                    continue;

                if (v1_dist.inf || edge_weight + v2_dist < v1_dist) {
                    weightToCalc = edge_weight + v2_dist;
                    v1_dist = weightToCalc;
                }
                if (weightToCalc == 0)
                    break;
            }

        sync_mutex.lock();
        if (nextToGo != graph.end()) {
            vert = (*nextToGo).first;
            nextToGo++;
        }
        else{
            sync_mutex.unlock();
            break;
        }
        sync_mutex.unlock();
    }
}

std::map<Graph::Vid, Graph::Weight> fordAlgorithmJustDistance(Graph::Vid s, Graph const& graph){
    calc_mutex.lock();
    std::map<Graph::Vid, Graph::Weight> ret, retSwp;
    for(auto& vertex: graph) {
        ret[vertex.first] = vertex.first == s ? 0 : Graph::Weight{0, true};
        retSwp[vertex.first] = ret[vertex.first];
    }

    int active_threads = num_threads < graph.size() ? num_threads : graph.size();

    for(int i = 0, sz = graph.size() - 1; i < sz; ++i){

        std::vector<std::thread> threads;
        threads.reserve(active_threads);

        nextToGo = graph.begin();

        for(int j = 0; j < active_threads; ++j, ++nextToGo);

        auto it = graph.begin();

        for(int j = 0; j < active_threads; ++j, ++it)
            threads.emplace_back(fordAlgorithmSubRoutine, std::ref(graph), (*it).first, std::ref(retSwp), std::ref(ret));

        for(auto& thread: threads)
            thread.join();

        for(auto& node: ret){
            retSwp[node.first] = node.second;
        }
    }

    calc_mutex.unlock();

    return ret;
}
