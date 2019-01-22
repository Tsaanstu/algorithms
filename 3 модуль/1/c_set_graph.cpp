#include "c_set_graph.hpp"

CSetGraph::CSetGraph(unsigned int verticesNumber) :
    verticesNumber_(verticesNumber),
    out_(verticesNumber_),
    in_(verticesNumber_) {}

CSetGraph::CSetGraph(const IGraph &graph) :
    verticesNumber_(graph.VerticesCount()),
    out_(verticesNumber_),
    in_(verticesNumber_) {
    for (int i = 0; i < verticesNumber_; i++) {
        std::vector<int> vertices = GetNextVertices(i);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

void CSetGraph::AddEdge(int from, int to) {
    out_[from].insert(to);
    in_[to].insert(from);
}

int CSetGraph::VerticesCount() const {
    return verticesNumber_;
}

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (int i : out_[vertex]) {
        vertices.push_back(i);
    }
    return vertices;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (int i : in_[vertex]) {
        vertices.push_back(i);
    }
    return vertices;
}