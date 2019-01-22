#include "c_arc_graph.hpp"

CArcGraph::CArcGraph(size_t vertices_count)
    : vertices_count_(vertices_count) {}

CArcGraph::CArcGraph(IGraph* graph) {
    int vertices_count = graph->VerticesCount();

    vertices_count_ = vertices_count;

    for (int i = 0; i < vertices_count; i++) {
        std::vector<int> next_vertices = graph->GetNextVertices(i);
        for (int next : next_vertices) {
            AddEdge(i, next);
        }
    }
}

void CArcGraph::AddEdge(int from, int to) {
    array_.push_back(std::make_pair(from, to));
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (auto element : array_) {
        if (element.first == vertex) {
            next.push_back(element.second);
        }
    }
    return next;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (auto element : array_) {
        if (element.second == vertex) {
            prev.push_back(element.first);
        }
    }
    return prev;
}