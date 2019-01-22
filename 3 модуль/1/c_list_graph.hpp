#ifndef M3_1_C_LIST_GRAPH_HPP
#define M3_1_C_LIST_GRAPH_HPP

#include <list>

#include "IGraph.hpp"

class CListGraph : IGraph {
 public:
    CListGraph(int n) : liste_d_adjacence_(n) {};
    explicit CListGraph(const IGraph &copiant);

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
 private:
    std::vector<std::list<int>> liste_d_adjacence_;  //  матрица смежностей
};

#endif //M3_1_C_LIST_GRAPH_HPP
