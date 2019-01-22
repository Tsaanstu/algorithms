#ifndef M3_1_C_MATRIX_GRAPH_HPP
#define M3_1_C_MATRIX_GRAPH_HPP

#include "IGraph.hpp"

class CMatrixGraph : public IGraph {
 public:
    CMatrixGraph(int n) : liste_d_adjacence_(n) {};
    explicit CMatrixGraph(const IGraph &copiant);

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;
 private:
    std::vector<std::vector<int>> liste_d_adjacence_;
};

#endif //M3_1_C_MATRIX_GRAPH_HPP
