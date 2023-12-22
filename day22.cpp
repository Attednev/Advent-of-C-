#include "day0.h"

struct brick {
    std::size_t start_x;
    std::size_t start_y;
    std::size_t start_z;
    std::size_t end_x;
    std::size_t end_y;
    std::size_t end_z;
};

std::size_t hash(auto& block) {
    auto& [x1, y1, z1, x2, y2, z2]=block;
    return std::hash<std::string>{}(std::to_string(x1) + "," + std::to_string(y1) + "," + std::to_string(z1) + ","
                                    + std::to_string(x2) + "," + std::to_string(y2) + "," + std::to_string(z2));
}

bool intersect_disregard_z(auto& a, auto& b) {
    return !(a.start_x > b.end_x || b.start_x > a.end_x || a.start_y > b.end_y || b.start_y > a.end_y);
}

std::size_t disintegration_count(auto& blocks, auto& dependency_list) {
    // Sort based on z-coordinate, so when we visit a brick we can immediately see which dependencies there are
    std::sort(blocks.begin(), blocks.end(), [](auto& a, auto& b) {
        return a.start_z < b.start_z;
    });

    std::unordered_map<std::size_t, std::vector<std::size_t>> dependency_count{};
    for (signed i = 0; i < blocks.size(); i++) {
        std::vector<std::vector<std::size_t>> dependency_list_per_z(350);
        for (signed j = 0; j < i; j++)
            if (intersect_disregard_z(blocks[i], blocks[j]))
                dependency_list_per_z[blocks[j].end_z].emplace_back(hash(blocks[j]));
        while (blocks[i].start_z > 1 && dependency_list_per_z[blocks[i].start_z - 1].empty()) {
            blocks[i].start_z--;
            blocks[i].end_z--;
        }
        if (dependency_list_per_z[blocks[i].start_z - 1].size() == 1)
            dependency_count[dependency_list_per_z[blocks[i].start_z - 1][0]].emplace_back(hash(blocks[i]));
        dependency_list[hash(blocks[i])] = dependency_list_per_z[blocks[i].start_z - 1];
    }
    return blocks.size() - dependency_count.size();
}

std::size_t count_falling_bricks(auto& blocks, auto& dependency_list) {
    // Sort based on z-coordinate (primary) and number of dependencies (secondary), so bricks that are being depended on
    // fall before the brick that depends on them
    std::sort(blocks.begin(), blocks.end(), [&dependency_list](auto& a, auto& b) {
        return a.start_z < b.start_z || (a.start_z == b.start_z && dependency_list[hash(a)] < dependency_list[hash(b)]);
    });

    std::size_t sum_of_chain_reactions{0};
    for (auto& block : blocks) {
        std::unordered_map<std::size_t, bool> falling_bricks{{hash(block), true}};
        for (auto& b : blocks) {
            if (falling_bricks.contains(hash(b)) || dependency_list[hash(b)].empty() || dependency_list[hash(b)].size() > falling_bricks.size())
                continue;
            if (!std::any_of(dependency_list[hash(b)].begin(), dependency_list[hash(b)].end(), [&falling_bricks](auto n) { return !falling_bricks.contains(n); }))
                falling_bricks[hash(b)] = true;
        }
        sum_of_chain_reactions += falling_bricks.size() - 1;
    }
    return sum_of_chain_reactions;
}

void solve(const std::vector<std::string>& lines) {
    std::vector<brick> bricks{};
    for (auto& line : trim_lines(lines)) {
        auto splits{split(line, '~')};
        auto start_pos{to_number_vector(split(splits[0], ','))};
        auto end_pos{to_number_vector(split(splits[1], ','))};
        bricks.emplace_back(start_pos[0], start_pos[1], start_pos[2], end_pos[0], end_pos[1], end_pos[2]);
    }

    std::unordered_map<std::size_t, std::vector<std::size_t>> dependency_list{};
    std::cout << "1) Result is " << disintegration_count(bricks, dependency_list) << std::endl;
    std::cout << "2) Result is " << count_falling_bricks(bricks, dependency_list) << std::endl;

}

int main() {
    solve(read_input_file("../inputs/day22"));
}
