#include "day0.h"

enum stack_state { PUSH, INVALID, POP };

struct pda_node {
    stack_state state{PUSH};
    std::stack<std::size_t> stack{};
    std::size_t smudge{range_index::npos};
};

std::size_t get_binary_from_string(const std::string& str) {
    std::size_t value{0};
    for (auto& symbol: str) value = (value << 1) | (symbol == '#' ? 1 : 0);
    return value;
}

std::pair<std::size_t, bool> find_mirror_horizontal(std::vector<std::string>& lines, bool contains_smudges) {
    std::vector<pda_node> nodes(lines.size() - 1);
    std::size_t next_to_transition{0};
    for (std::size_t i = 0; i < lines.size(); i++) {
        std::size_t stack_symbol{get_binary_from_string(lines[i])};
        for (std::size_t j = 0; j < nodes.size(); j++) {
            if (nodes[j].state == INVALID) continue;
            else if (nodes[j].state == PUSH) nodes[j].stack.push(stack_symbol);
            else if (!nodes[j].stack.empty()) {
                if (nodes[j].stack.top() != stack_symbol) {
                    if (!contains_smudges || std::popcount(nodes[j].stack.top() ^ stack_symbol) != 1 || nodes[j].smudge != range_index::npos) nodes[j].state = INVALID;
                    else nodes[j].smudge = i;
                }
                nodes[j].stack.pop();
            }
            if (j == next_to_transition && nodes[j].state == PUSH) nodes[j].state = POP;
        }
        next_to_transition++;
    }

    for (std::size_t i = 0; i < nodes.size(); i++)
        if (nodes[i].state != INVALID && (!contains_smudges || nodes[i].smudge != range_index::npos)) {
            if (nodes[i].smudge != range_index::npos)
                lines[nodes[i].smudge] = lines[2 * i + 1 - nodes[i].smudge];
            return std::make_pair(i + 1, nodes[i].smudge != range_index::npos);
        }
    return std::make_pair(range_index::npos, false);
}

std::pair<std::size_t, bool> find_mirror_vertical(const std::vector<std::string>& lines, bool contains_smudges) {
    std::vector<std::string> transposed_lines(lines[0].size(), "");
    for (auto& line : lines)
        for (std::size_t i = 0; i < line.length(); i++)
            transposed_lines[i] += line[i];
    return find_mirror_horizontal(transposed_lines, contains_smudges);
}

std::size_t summarize_notes(const std::vector<std::string>& lines, bool contains_smudges = false) {
    std::size_t total{0};
    std::vector<std::string> current_set{};
    for (auto& line : lines) {
        if (!trim(line).empty()) {
            current_set.push_back(trim(line));
            continue;
        }
        auto [horizontal, h_corrected] = find_mirror_horizontal(current_set, contains_smudges);
        auto [vertical, v_corrected] = find_mirror_vertical(current_set, contains_smudges && !h_corrected);
        if (horizontal != range_index::npos && (!contains_smudges || h_corrected)) total += horizontal * 100;
        else if (vertical != range_index::npos && (!contains_smudges || v_corrected)) total += vertical;
        current_set.clear();
    }
    return total;
}

void solve(const std::vector<std::string>& lines) {
    std::cout << "1) Result is " << summarize_notes(lines) << std::endl;
    std::cout << "2) Result is " << summarize_notes(lines, true) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day13"));
}
