#include "../day0.h"

struct node {
    const std::string left;
    const std::string right;
};

std::size_t gcd(std::size_t a, std::size_t b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

std::size_t lcm(std::vector<std::size_t>& distances) {
    std::size_t lcm{1};
    for (std::size_t d : distances)
        lcm *= d / gcd(lcm, d);
    return lcm;
}

std::vector<std::string> get_starting_nodes(std::unordered_map<std::string, node>& translation) {
    std::vector<std::string> nodes{};
    for (auto& [k, v] : translation)
        if (k[2] == 'A')
            nodes.push_back(k);
    return nodes;
}

std::size_t find_end_node(std::unordered_map<std::string, node>& translation, std::string& instructions, std::string start, std::variant<std::string, char> end) {
    std::size_t instruction_pointer{0};
    std::size_t number_of_steps{0};
    while ((std::holds_alternative<std::string>(end) && start != std::get<std::string>(end))
            || (std::holds_alternative<char>(end) && start[2] != std::get<char>(end))) {
        start = instructions[instruction_pointer] == 'R' ? translation[start].right : translation[start].left;
        instruction_pointer = (instruction_pointer + 1) % instructions.length();
        number_of_steps++;
    }
    return number_of_steps;
}

std::size_t find_ghost_end_nodes(std::unordered_map<std::string, node>& translation, std::string& instructions) {
    std::vector<std::size_t> distance_to_end_node{};
    for (auto& node : get_starting_nodes(translation))
        distance_to_end_node.push_back(find_end_node(translation, instructions, node, 'Z'));
    return lcm(distance_to_end_node);
}

void get_translation_table(const std::vector<std::string>& lines, std::unordered_map<std::string, node>& translation) {
    for (std::size_t i = 2; i <= lines.size(); i++) {
        if (lines[i].length() == 0)
            continue;
        std::vector<std::string> splits{split(lines[i])};
        translation.insert({splits[0], {splits[2].substr(1, 3), splits[3].substr(0, 3)}});
    }
}

void solve(const std::vector<std::string>& lines) {
    std::string instructions{trim(lines[0])};
    std::unordered_map<std::string, node> translation{};
    get_translation_table(lines, translation);
    std::size_t number_of_steps{find_end_node(translation, instructions, "AAA", "ZZZ")};
    std::size_t number_of_ghost_steps{find_ghost_end_nodes(translation, instructions)};
    std::cout << "1) Result is " << number_of_steps << std::endl;
    std::cout << "2) Result is " << number_of_ghost_steps << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day08"));
}