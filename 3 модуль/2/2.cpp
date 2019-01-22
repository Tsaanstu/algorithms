#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

class Graph {
 public:
    Graph(size_t _v, size_t _n);
    void remplissage();
    void requete_de_vertex();
    void output();
    size_t bfs(size_t _u, size_t _w);
 private:
    size_t v_;  //  кол-во вершин
    size_t n_;  //  кол-во ребёр
    std::vector<std::vector<int>> data_;
};

int main() {
    size_t elem, n;
    std::cin >> elem >> n;
    Graph graph(elem, n);
    graph.remplissage();
//    graph.output();
    graph.requete_de_vertex();
}

void Graph::output() {
    std::cout << "output:" << std::endl;
    for (size_t i = 0; i < data_.size(); ++i) {
        for (size_t j = 0; j < data_[i].size(); ++j) {
            std::cout << data_[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "end output" << std::endl;
}

size_t Graph::bfs(size_t u, size_t w) {
    std::vector<bool> visitates;
    std::queue<int> queue_;
    std::vector<int> distance(data_.size(), INT_MAX);
    std::vector<int> route(data_.size(), 0);
    //  init
    for (size_t i = 0; i < data_.size(); ++i) {
        visitates.push_back(false);
    }
    for (size_t i = 0; i < data_[u].size(); ++i) {
        route[data_[u][i]] = 1;
    }
    route[u] = 1;
    queue_.push(u);
    distance[u] = 0;

    while (!queue_.empty()) {
        int elem = queue_.front();  //  новая вершина из очереди
        queue_.pop();
        visitates[elem] = true;
        for (size_t i = 0; i < data_[elem].size(); ++i) {
            if ((distance[elem] + 1) == distance[data_[elem][i]]) {
                route[data_[elem][i]] += route[elem];
            } else if (distance[elem] + 1 < distance[data_[elem][i]]) {
                distance[data_[elem][i]] = distance[elem] + 1;
                route[data_[elem][i]] = route[elem];
            }
            if (!visitates[data_[elem][i]]) {
                queue_.push(data_[elem][i]);
                visitates[data_[elem][i]] = true;
//                distance[i] = distance[elem] + 1;
            }
        }
    }
    return route[w];
}

void Graph::requete_de_vertex() {
    size_t u, w;
    std::cin >> u >> w;
    std::cout << bfs(u, w) << std::endl;
}

void Graph::remplissage() {
    int from, to;
    for (size_t i = 0; i < n_; ++i) {
        std::cin >> from >> to;
        data_[from].push_back(to);
        data_[to].push_back(from);
    }
}

Graph::Graph(size_t _v, size_t _n) : v_(_v), n_(_n) {
    data_ = std::vector < std::vector < int >> (v_);
}