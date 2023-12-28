#include "day0.h"

struct collapsed_node {
    std::vector<std::size_t> edges{};
    std::size_t length{0};
    bool is_slope{false};
};

std::size_t hash(auto x, auto y) {
    return std::hash<std::string>{}(std::to_string(x) + "," + std::to_string(y));
}

std::vector<std::size_t> get_neighbours(auto& lines, auto x, auto y) {
    std::vector<std::size_t> neighbours{};
    if (lines[y][x] == '>')
        neighbours.push_back(hash(x + 1, y));
    if (lines[y][x] == '<')
        neighbours.push_back(hash(x - 1, y));
    if (lines[y][x] == 'v')
        neighbours.push_back(hash(x, y + 1));
    if (lines[y][x] == '.') {
        if (x + 1 < lines[0].length() && lines[y][x + 1] != '#') neighbours.push_back(hash(x + 1, y));
        if (y + 1 < lines.size() && lines[y + 1][x] != '#') neighbours.push_back(hash(x, y + 1));
        if (x > 0 && lines[y][x - 1] != '#') neighbours.push_back(hash(x - 1, y));
        if (y > 0 && lines[y - 1][x] != '#') neighbours.push_back(hash(x, y - 1));
    }
    return neighbours;
}

void find_max_path(auto& graph, auto& collapse_target, auto end, auto current, auto& visited, std::size_t& max, std::size_t length = 0) {
    if (!graph.contains(current))
        current = collapse_target[current];

    if (current == end) {
        max = std::max(max, length + graph[current].length - 1);
        return;
    }
    visited[current] = true;
    auto e = graph[current].edges;
    for (auto& next : graph[current].edges)
        if (!visited[next])
            find_max_path(graph, collapse_target, end, next, visited, max, length + graph[current].length);
    visited[current] = false;
}

void collapse_graph(auto& graph, auto& collapse_target, auto& visited, auto current, auto last_visited) {
    if (!graph.contains(current) || graph[current].edges.empty())
        return;
    std::size_t next{graph[current].is_slope ? 0 : current};
    std::size_t last{0};
    if (graph[current].edges.size() <= 2 && !graph[current].is_slope) {
        visited[current] = true;
        while (true) {
            last = next;
            next = graph[current].edges.back();
            if (next == last_visited) {
                std::swap(graph[current].edges[0], graph[current].edges[graph[current].edges.size() - 1]);
                next = graph[current].edges.back();
            }
            if (!graph.contains(next)) {
                next = collapse_target[next];
                graph[current].edges[graph[current].edges.size() - 1] = next;
            }
            if (graph[next].edges.size() != 2)
                break;
            collapse_target[next] = current;
            graph[current].edges.pop_back();
            graph[current].edges.push_back(graph[next].edges[graph[next].edges[0] == last ? 1 : 0]);
            graph[current].length += graph[next].length;
            graph.erase(next);
        }
    }
    for (auto& next_fragment : graph[next].edges) {
        if (!graph.contains(next_fragment))
            next_fragment = collapse_target[next_fragment];
        if (!visited[next_fragment])
            collapse_graph(graph, collapse_target, visited, next_fragment, next);
    }
}

auto create_graph(auto& lines) {
    std::unordered_map<std::size_t, collapsed_node> nodes{};
    std::size_t start_node{};
    std::size_t end_node{};
    for (std::size_t i = 0; i < lines.size(); i++) {
        for (std::size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '#') continue;
            if (i == 0) start_node = hash(j, i);
            if (i == lines.size() - 1) end_node = hash(j, i);
            nodes[hash(j, i)] = {{}, 1, contains({'>', '<', 'v'}, lines[i][j])};
        }
    }
    for (std::size_t i = 0; i < lines.size(); i++) {
        for (std::size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '#') continue;
            for (auto neighbour : get_neighbours(lines, j, i)) {
                nodes[hash(j, i)].edges.push_back(neighbour);
            }
        }
    }
    return std::make_tuple(nodes, start_node, end_node);
}

std::size_t get_hike_length(auto& lines) {
    auto [graph, start_node, end_node] = create_graph(lines);
    std::unordered_map<std::size_t, std::size_t> collapse_target{};
    std::unordered_map<std::size_t, bool> visited{};
    collapse_graph(graph, collapse_target, visited, start_node, 0);

    visited.clear();
    std::size_t max{0};
    find_max_path(graph, collapse_target, collapse_target.contains(end_node) ? collapse_target[end_node] : end_node, start_node, visited, max);
    return max;
}

void solve(const std::vector<std::string>& input) {
    std::vector<std::string> lines{trim_lines(input)};

    std::cout << "1) Result is " << get_hike_length(lines) << std::endl;

    for (auto& line : lines)
        for (char& symbol : line)
            if (symbol != '#' && symbol != '.')
                symbol = '.';

    std::cout << "2) Result is " << get_hike_length(lines) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day23"));
}
