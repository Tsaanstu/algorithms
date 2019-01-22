#include <string>
#include <array>
#include <vector>
#include <utility>
#include <assert.h>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <iostream>
#include <unistd.h>
#include <cmath>

struct position {
    std::array<char, 16> chips;
    int zero_position;
    int h;
    bool IsFinish() const;
    std::vector<position> Siblings() const;

    bool operator==(const position &other) const;
    bool operator!=(const position &other) const { return !operator==(other); }
    bool operator<(const position& pos) const {
        return chips < pos.chips;
    }

    bool operator>(const position& pos) const {
        return chips > pos.chips;
    }
};

const position kFinishPosition{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}, 15};

namespace std {
template<>
struct hash<position> {
    size_t operator()(const position &pos) const {
        size_t hash = 0;
        for (const auto &chip: pos.chips) {
            hash = hash * 37 + chip;
        }
        return hash;
    }
};
}

std::pair<int, std::string> SolvePuzzle16(const position &pos);

char GetTurnSymbol(const position &from, const position &to) {
    const int zero_position_diff = to.zero_position - from.zero_position;
    switch (zero_position_diff) {
        case 4: return 'U';
        case -4: return 'D';
        case 1: return 'L';
        case -1: return 'R';
        default: assert(false);
    }
}

int h(position v) {
    int h = 0;
    for (int i = 0; i < v.chips.size(); ++i) {
        if (!v.chips[i]) {
            h += 20 * (std::abs(3 - i % 4) + std::abs(3 - std::floor(i / 4)));
        } else {
            h += 20 * (std::abs(i % 4 - (v.chips[i] - 1) % 4) + std::abs(std::floor(i / 4) - std::floor((v.chips[i] - 1) / 4)));
        }
    }
    return h;
}

std::vector<position> get_next_position(position current) {
    std::vector<position> next;
    size_t zero_pos = 0, it = 0;

    while(current.chips[zero_pos] != 0) {
        ++zero_pos;
    }

    if (zero_pos < 15 && zero_pos % 4 != 3) {
        next.push_back(current);
        std::swap(next[it].chips[zero_pos], next[it].chips[zero_pos + 1]);
        next[it].zero_position++;
        ++it;
    }
    if (zero_pos > 0 && zero_pos % 4 != 0) {
        next.push_back(current);
        std::swap(next[it].chips[zero_pos], next[it].chips[zero_pos - 1]);
        next[it].zero_position--;
        ++it;
    }
    if (zero_pos >= 4) {
        next.push_back(current);
        std::swap(next[it].chips[zero_pos], next[it].chips[zero_pos - 4]);
        next[it].zero_position -= 4;
        ++it;
    }
    if (zero_pos <= 11) {
        next.push_back(current);
        std::swap(next[it].chips[zero_pos], next[it].chips[zero_pos + 4]);
        next[it].zero_position += 4;
        ++it;
    }
    return next;
}

bool astar(const position &start, std::unordered_map<position, position> &parents) {
    std::priority_queue<std::pair<int, position>,
                        std::vector<std::pair<int, position>>,
                        std::greater<std::pair<int, position>>> astar_queue;
    astar_queue.emplace(0, start);
    while (!astar_queue.empty()) {
        position current = astar_queue.top().second;
        astar_queue.pop();
        for (const auto& pos : get_next_position(current)) {
            if (parents.find(pos) == parents.end()) {
                parents.emplace(pos, current);
                if (pos.IsFinish()) {
                    return true;
                }
                astar_queue.emplace(h(pos), pos);
            }
        }
    }
    return false;
}

std::string GetPath(const position &start,
                    const std::unordered_map<position, position> &parents) {
    std::string path;
    position current = kFinishPosition;
    while (current != start) {
        position parent = parents.at(current);
        path.push_back(GetTurnSymbol(parent, current));
        current = parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::pair<int, std::string> SolvePuzzle16(const position &start) {
    std::unordered_map<position, position> parents;
    if (!astar(start, parents)) {
        return std::pair<int, std::string>(-1, std::string());
    }
    const std::string path = GetPath(start, parents);
    return std::pair<int, std::string>(path.size(), path);
}

bool position::IsFinish() const {
    return operator==(kFinishPosition);
}

bool position::operator==(const position &other) const {
    return chips == other.chips;
    // Zero position must be equal for equal chips
}

int main() {
    unsigned short int num;
    int pos = -1;
    std::array<char, 16> test;
    for (size_t i = 0; i < 16; ++i) {
        std::cin >> num;
        if (num == 0) {
            pos = i;
        }
        test[i] = num;
    }
    if (pos < 0) {
        std::cout << -1;
        return 0;
    }
    position start{test, pos};
    const auto solution = SolvePuzzle16(start);
    std::cout << solution.first << std::endl << solution.second << std::endl;
    return 0;
}