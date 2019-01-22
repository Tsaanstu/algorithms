#ifndef M3_1_C_ARC_GRAPH_HPP
#define M3_1_C_ARC_GRAPH_HPP

#include "IGraph.hpp"

class CArcGraph : public IGraph {
 public:
    explicit CArcGraph(size_t vertices_count);
    CArcGraph(IGraph *graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override { return vertices_count_; }

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    int vertices_count_;
    std::vector<std::pair<int, int>> array_;
};

#endif //M3_1_C_ARC_GRAPH_HPP
