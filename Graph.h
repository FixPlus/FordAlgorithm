//
// Created by Бушев Дмитрий on 08.05.2021.
//

#ifndef FORDALGORITHM_GRAPH_H
#define FORDALGORITHM_GRAPH_H
#include <vector>
#include <map>
#include <ostream>

class Graph{
public:
    typedef int Vid;
    struct Vertex;


    struct Weight{
        int weight;
        bool inf;
        Weight(int w = 0, bool i = false): weight(w), inf(i){};

        bool operator>(Weight const& another) const{
            if(inf || another.inf)
                return false;
            return weight > another.weight;
        }
        bool operator<(Weight const& another) const{
            if(inf || another.inf)
                return false;
            return weight < another.weight;
        }
        bool operator==(Weight const& another) const{
            if(inf || another.inf)
                return false;
            return weight == another.weight;
        }

        bool operator!=(Weight const& another) const{
            return !(*this == another);
        }

        Weight const& operator+=(Weight const& another) {
            if(another.inf)
                inf = true;
            weight += another.weight;
            return *this;
        }

        Weight const& operator-=(Weight const& another) {
            if(another.inf)
                inf = true;
            weight -= another.weight;
            return *this;
        }

        Weight operator+(Weight const& another) const {
            Weight ret = *this;
            ret += another;
            return ret;
        }

        Weight operator-(Weight const& another) const{
            Weight ret = *this;
            ret -= another;
            return ret;
        }


    };
    struct Vertex{
        std::map<Vid, Weight> edges;
    };
private:

    std::map<Vid, Vertex> vertices;

public:
    void addVertex(Vid id);
    void addEdge(Vid from, Vid to, int weight);
    Graph::Weight getEdge(Vid from, Vid to) const;
    bool hasVertex(Vid id) const;

    size_t size() const{
        return vertices.size();
    }
    auto begin(){
        return vertices.begin();
    }

    auto begin() const{
        return vertices.begin();
    }

    auto end() {
        return vertices.end();
    }

    auto end() const{
        return vertices.end();
    }

    auto at(size_t id){
        return vertices.at(id);
    }

    auto at(size_t id) const{
        return vertices.at(id);
    }

    void clear(){
        vertices.clear();
    }
};

std::ostream& operator<<(std::ostream& stream, Graph::Weight const& weight);
std::ostream& operator<<(std::ostream& stream, Graph const& graph);

#endif //FORDALGORITHM_GRAPH_H
