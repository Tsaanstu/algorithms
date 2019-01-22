//#ifndef M3_1_C_SET_GRAPH_HPP
//#define M3_1_C_SET_GRAPH_HPP
//
//class CSetGraph {
//
//};
//
//#endif //M3_1_C_SET_GRAPH_HPP


#ifndef C_SET_GRAPH_HPP
#define C_SET_GRAPH_HPP

#include <unordered_set>
#include <list>

#include "IGraph.hpp"

class CSetGraph : IGraph {
 public:
    CSetGraph(unsigned int verticesNumber);
    explicit CSetGraph(const IGraph &copiant);

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
 private:
    unsigned int verticesNumber_;
    std::vector<std::unordered_set<int>> out_;
    std::vector<std::unordered_set<int>> in_;
};

#endif //C_SET_GRAPH_HPP