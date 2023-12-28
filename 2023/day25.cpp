#include <random>
#include "day0.h"

struct edge {
    std::string from,  to;
    bool operator==(const edge& other) const { return (from == other.from && to == other.to) || (from == other.to && to == other.from); }
};

auto kargers_algorithm(auto& vertices, auto edges) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::unordered_map<std::string, std::size_t> set_of_vertex{};
    for (auto& [n, v] : vertices)
        set_of_vertex[n] = set_of_vertex.size();

    for (std::size_t iteration = 0; iteration < set_of_vertex.size() - 2; ) {
        std::uniform_int_distribution<> distribution(0, edges.size() - 1);
        auto edge_to_contract{edges[distribution(gen)]};
        auto set_left{set_of_vertex[edge_to_contract.from]};
        auto set_right{set_of_vertex[edge_to_contract.to]};
        edges.erase(std::find(edges.begin(), edges.end(), edge_to_contract));
        if (set_left == set_right) continue;
        for (auto& [_, i] : set_of_vertex)
            if (i == set_right)
                i = set_left;
        iteration++;
    }

    std::unordered_map<std::size_t, std::size_t> vertices_in_set{};
    for (auto& [vertex, set] : set_of_vertex)
        vertices_in_set[set]++;

    std::size_t number_of_edges_connecting{0};
    for (auto& [s, e] : edges)
        if (set_of_vertex[s] != set_of_vertex[e])
            number_of_edges_connecting++;

    return std::make_pair(std::accumulate(vertices_in_set.begin(), vertices_in_set.end(), 1ul, [](auto acc, auto e) { return acc * e.second; }),
                          std::count_if(edges.begin(), edges.end(), [&set_of_vertex](auto e) { return set_of_vertex[e.from] != set_of_vertex[e.to]; }));
}

std::size_t min_cut(auto& vertices, auto& edges) {
    std::pair<std::size_t, std::size_t> result;
    while ((result = kargers_algorithm(vertices, edges)).second != 3) {}
    return result.first;
}

void solve(const std::vector<std::string>& input) {
    std::unordered_map<std::string, std::vector<std::string>> vertices{};
    std::vector<edge> edges{};
    for (auto& line : trim_lines(input)) {
        auto splits{split(line, ": ")};
        for (auto& destination : split(splits[1])) {
            vertices[splits[0]].emplace_back(destination);
            vertices[destination].emplace_back(splits[0]);
            edges.emplace_back(splits[0], destination);
        }
    }
    std::cout << "Because this is a randomized algorithm this process might take some time (not too long though)" << std::endl;
    std::cout << "1) Result is " << min_cut(vertices, edges) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day25"));
}
