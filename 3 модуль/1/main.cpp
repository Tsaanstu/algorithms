#include <iostream>
#include "c_list_graph.hpp"
#include "c_matrix_graph.hpp"
#include "c_arc_graph.hpp"
#include "c_set_graph.hpp"

bool test_CListGraph();
bool test_CMatrixGraph();
bool test_CArcGraph();
bool test_CSetGraph();

int main() {
    if (test_CListGraph()) {
        std::cout << std::endl << "\"CListGraph\" est testé" << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    if (test_CMatrixGraph()) {
        std::cout << std::endl << "\"CMatrixGraph\" est testé" << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    if (test_CArcGraph()) {
        std::cout << std::endl << "\"CArcGraph\" est testé" << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    if (test_CSetGraph()) {
        std::cout << std::endl << "\"CSetGraph\" est testé" << std::endl;
    }
    return 0;
}

bool test_CSetGraph() {
    CSetGraph graphe(5);
    graphe.AddEdge(0, 1);
    graphe.AddEdge(0, 2);
    graphe.AddEdge(1, 3);
    graphe.AddEdge(2, 4);
    graphe.AddEdge(3, 4);

    std::cout << "GetNextVertices:" << std::endl;
    for (int i : graphe.GetNextVertices(0)) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "GetPrevVertices:" << std::endl;
    for (int i : graphe.GetPrevVertices(4)) {
        std::cout << i << " ";
    }
    return true;
}

bool test_CArcGraph() {
    CArcGraph graphe(5);
    graphe.AddEdge(0, 1);
    graphe.AddEdge(0, 2);
    graphe.AddEdge(1, 3);
    graphe.AddEdge(2, 4);
    graphe.AddEdge(3, 4);

    std::cout << "GetNextVertices:" << std::endl;
    for (int i : graphe.GetNextVertices(0)) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "GetPrevVertices:" << std::endl;
    for (int i : graphe.GetPrevVertices(4)) {
        std::cout << i << " ";
    }
    return true;
}

bool test_CMatrixGraph() {
    CMatrixGraph graphe(5);
    graphe.AddEdge(0, 1);
    graphe.AddEdge(0, 2);
    graphe.AddEdge(1, 3);
    graphe.AddEdge(2, 4);
    graphe.AddEdge(3, 4);

    std::cout << "GetNextVertices:" << std::endl;
    for (int i : graphe.GetNextVertices(0)) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "GetPrevVertices:" << std::endl;
    for (int i : graphe.GetPrevVertices(4)) {
        std::cout << i << " ";
    }
    return true;
}

bool test_CListGraph() {
    CListGraph graphe(5);
    graphe.AddEdge(0, 1);
    graphe.AddEdge(0, 2);
    graphe.AddEdge(1, 3);
    graphe.AddEdge(2, 4);
    graphe.AddEdge(3, 4);

    std::cout << "GetNextVertices:" << std::endl;
    for (int i : graphe.GetNextVertices(0)) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "GetPrevVertices:" << std::endl;
    for (int i : graphe.GetPrevVertices(4)) {
        std::cout << i << " ";
    }
    return true;
}