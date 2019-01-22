#include "c_list_graph.hpp"

void CListGraph::AddEdge(int from, int to) {
    liste_d_adjacence_[from].push_front(to);
}

int CListGraph::VerticesCount() const {
    return liste_d_adjacence_.size();  //  to int?
}

CListGraph::CListGraph(const IGraph &copiant) {
    size_t c_size = copiant.VerticesCount();
    liste_d_adjacence_ = std::vector<std::list<int>>(c_size);
    for (size_t i = 0; i < c_size; ++i) {
        std::vector<int> vertices = GetNextVertices(i);
        for (size_t j = 0; j < vertices.size(); ++j) {
            AddEdge(i, vertices[j]);
        }
    }
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (auto i : liste_d_adjacence_[vertex]) {
        vertices.push_back(i);
    }
    return vertices;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (size_t i = 0; i < liste_d_adjacence_.size(); ++i) {
        for (auto j : liste_d_adjacence_[i]) {
            if (j == vertex) {
                vertices.push_back(i);
            }
        }
    }
    return vertices;
}