#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <set>
#include <algorithm>

class priority_queue_with_erase : public std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
std::greater<std::pair<int, int>>> {
public:
void erase(const std::pair<int, int> &value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
    }
}
bool find(const std::pair<int, int> &value) {
    if (auto it = std::find(this->c.begin(), this->c.end(), value) != this->c.end()) {
        return true;
    }
    return false;
}
};

class Graph {
 public:
    Graph(size_t _N, size_t _M);
    void remplissage();
    void requete_de_vertex();
    void output();
    void trouver_moyen_rentable();
    std::vector<int> dijkstra_priority_queue(size_t u);
    std::vector<int> dijkstra_set(size_t u);
 private:
    size_t N_;  //  кол-во вершин
    size_t M_;  //  кол-во ребёр (путей)
    std::vector<std::vector<std::pair < int, int>>>
    data_;
};

int main() {
    size_t elem, n;
    std::cin >> elem >> n;
    Graph graph(elem, n);
    graph.remplissage();
//    graph.output();
    graph.trouver_moyen_rentable();
}

std::vector<int> Graph::dijkstra_priority_queue(size_t u) {
    std::vector<int> distance(N_, INT_MAX);
    priority_queue_with_erase queue_;
    distance[u] = 0;
    /*for (size_t i = 0; i < N_; ++i) {
        queue_.emplace(std::pair(distance[i], i));
    }*/
    queue_.emplace(std::pair(distance[u], u));
    while (!queue_.empty()) {
        auto min_distance = queue_.top();
        queue_.pop();
        for (size_t i = 0; i < data_[min_distance.second].size(); ++i) {
            if (distance[min_distance.second] + data_[min_distance.second][i].second
                < distance[data_[min_distance.second][i].first]) {
                if (queue_.find(std::pair(distance[data_[min_distance.second][i].first], data_[min_distance.second][i].first))) {
                    queue_.erase(std::pair(distance[data_[min_distance.second][i].first], data_[min_distance.second][i].first));
                }
                queue_.erase(std::pair(distance[data_[min_distance.second][i].first], data_[min_distance.second][i].first));
                distance[data_[min_distance.second][i].first] = distance[min_distance.second] + data_[min_distance.second][i].second;
                queue_.emplace(std::pair(distance[data_[min_distance.second][i].first], data_[min_distance.second][i].first));

            }
        }
    }
    return distance;
}

std::vector<int> Graph::dijkstra_set(size_t u) {
    std::vector<int> distance(N_, INT_MAX);
    std::set<std::pair<int, int>> queue_;
    distance[u] = 0;
//    for (size_t i = 0; i < N_; ++i) {
//        queue_.insert(std::pair(distance[i], i));
//    }
    queue_.insert(std::pair(distance[u], u));
    while (!queue_.empty()) {
        auto min_distance = *queue_.begin();
        queue_.erase(queue_.begin());
        for (size_t i = 0; i < data_[min_distance.second].size(); ++i) {
            if (distance[min_distance.second] + data_[min_distance.second][i].second
                < distance[data_[min_distance.second][i].first]) {
                if (queue_.find(std::pair(distance[data_[min_distance.second][i].first], data_[min_distance.second][i].first)) != queue_.end()) {
                    queue_.erase(queue_.find(std::pair(distance[data_[min_distance.second][i].first], data_[min_distance.second][i].first)));
                }
                distance[data_[min_distance.second][i].first] = distance[min_distance.second] + data_[min_distance.second][i].second;
                queue_.insert(std::pair(distance[data_[min_distance.second][i].first], data_[min_distance.second][i].first));
            }
        }
    }
    return distance;
}

void Graph::trouver_moyen_rentable() {
    size_t u, w;
    std::cin >> u >> w;
    std::cout << dijkstra_priority_queue(u)[w] << std::endl;
}

void Graph::output() {
    std::cout << "output:" << std::endl;
    for (size_t i = 0; i < data_.size(); ++i) {
        for (size_t j = 0; j < data_[i].size(); ++j) {
            std::cout << "(" << data_[i][j].first << "," << data_[i][j].second << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << "end output" << std::endl;
}

void Graph::remplissage() {
    int from, to, l;
    for (size_t i = 0; i < M_; ++i) {
        std::cin >> from >> to >> l;
        data_[from].push_back(std::pair(to, l));
        data_[to].push_back(std::pair(from, l));
    }
}

Graph::Graph(size_t _v, size_t _n) : N_(_v), M_(_n) {
    data_ = std::vector < std::vector < std::pair < int, int > >> (N_);
}