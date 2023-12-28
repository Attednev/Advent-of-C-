#include "day0.h"

enum direction { UP, RIGHT, DOWN, LEFT, NONE };
typedef std::pair<int, int> pair;

struct node {
    int x, y, cost, direction_count;
    direction direction_facing;
    bool operator>(const node& other) const { return cost > other.cost; }
    bool operator==(const node& other) const { return x == other.x && y == other.y && direction_facing == other.direction_facing && direction_count == other.direction_count; }
};

std::size_t hash(node n) {
    return std::hash<std::string>{}(std::to_string(n.x) + "," + std::to_string(n.y) + "," + std::to_string(n.direction_count) + "," + std::to_string(n.direction_facing));
}

direction get_direction(int dx, int dy) {
    if (dx == 0 && dy == 1) return DOWN;
    if (dx == 0 && dy == -1) return UP;
    if (dx == 1 && dy == 0) return RIGHT;
    return LEFT;
}

direction opposite(int dx, int dy) {
    auto direction{get_direction(dx, dy)};
    if (direction == UP) return DOWN;
    if (direction == DOWN) return UP;
    if (direction == LEFT) return RIGHT;
    return LEFT;
}

auto get_neighbours(auto& weights, auto x, auto y, auto c, auto dc, auto d, auto min_steps, auto max_steps) {
    std::vector<node> neighbours{};
    for (auto [delta_x, delta_y] : std::vector<pair>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}) {
        auto nx = x + delta_x;
        auto ny = y + delta_y;
        if (nx < 0 || nx >= weights[0].size() || ny < 0 || ny >= weights.size())
            continue;
        if (d == opposite(delta_x, delta_y))
            continue;
        auto cost = c + weights[ny][nx];
        if (d == get_direction(delta_x, delta_y) && dc < max_steps)
            neighbours.emplace_back(nx, ny, cost, dc + 1, d);
        if (d != get_direction(delta_x, delta_y) && (dc >= min_steps || d == NONE))
            neighbours.emplace_back(nx, ny, cost, 1, get_direction(delta_x, delta_y));
    }
    return neighbours;
}

std::size_t get_shortest_path(auto& weights, auto min_steps, auto max_steps) {
    std::vector<node> nodes{{0, 0, 0, 1, NONE}};
    std::unordered_map<std::size_t, bool> open_set{};
    std::unordered_map<std::size_t, bool> closed_set{};
    while (!nodes.empty()) {
        std::pop_heap(nodes.begin(), nodes.end(), std::greater<>{});
        auto& [x, y, c, dc, d] = nodes.back();
        nodes.pop_back();
        open_set.erase(hash({x, y, c, dc, d}));

        if (x == weights[0].size() - 1 && y == weights.size() - 1 && dc >= min_steps) return c;

        closed_set[hash({x, y, c, dc, d})] = true;
        for (auto& neighbour : get_neighbours(weights, x, y, c, dc, d, min_steps, max_steps)) {
            if (closed_set.contains(hash(neighbour)) || open_set.contains(hash(neighbour))) continue;
            open_set[hash(neighbour)] = true;
            nodes.push_back(neighbour);
            std::push_heap(nodes.begin(), nodes.end(), std::greater<>{});
        }
    }
    return 0;
}

void solve(const std::vector<std::string>& input) {
    auto lines = trim_lines(input);
    std::vector<std::vector<int>> weights(lines.size());
    for (std::size_t i = 0; i < lines.size(); i++)
        for (auto& c : lines[i])
            weights[i].emplace_back(std::stoul(std::string{c}));

    std::cout << "1) Result is " << get_shortest_path(weights, 1, 3) << std::endl;
    std::cout << "2) Result is " << get_shortest_path(weights, 4, 10) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day17"));
}
