#include "day0.h"

enum node_type { ENTRY, INNER, EXIT };

void trigger(std::vector<node_type>& nodes, std::vector<std::size_t>& visitors, char trigger) {
    std::vector<std::size_t> next_visitors(visitors.size(), 0);
    for (std::size_t index = 0; index < nodes.size(); index++) {
        if (trigger == '?') {
            if (nodes[index] == EXIT) next_visitors[index] += visitors[index];
            if (index + 1 < visitors.size()) next_visitors[index + 1] += visitors[index];
        } else if (trigger == '#' && (nodes[index] == EXIT || nodes[index] == INNER) && index + 1 < visitors.size()) {
            next_visitors[index + 1] += visitors[index];
        } else if (trigger == '.') {
            if (nodes[index] == EXIT) next_visitors[index] += visitors[index];
            if (nodes[index] == ENTRY && index + 1 < visitors.size()) next_visitors[index + 1] += visitors[index];
        }
    }
    visitors = std::move(next_visitors);
}

std::size_t get_number_of_arrangements(std::string& configuration, std::vector<std::size_t>& numbers) {
    std::vector<node_type> nodes{};
    for (auto n : numbers) {
        nodes.push_back(EXIT);
        for (std::size_t k = 1; k < n; k++)
            nodes.push_back(INNER);
        nodes.push_back(ENTRY);
    }
    nodes[nodes.size() - 1] = EXIT;

    std::vector<std::size_t> visitors(nodes.size(), 0);
    visitors[0]++;
    for (auto c : configuration)
        trigger(nodes, visitors, c);

    return visitors[visitors.size() - 1];
}

std::size_t get_sum_of_arrangements(const std::vector<std::string>& lines, std::size_t multiplier = 1) {
    std::size_t number_of_arrangements{0};
    for (auto& line : lines) {
        std::vector<std::string> splits{split(line, ' ')};
        std::vector<std::size_t> numbers{to_number_vector(split(splits[1], ','))};
        std::string multiplied_string;
        std::vector<std::size_t> multiplied_numbers{};
        for (std::size_t i = 0; i < multiplier; i++) {
            multiplied_string.append(splits[0]);
            for (std::size_t n : numbers) multiplied_numbers.push_back(n);
            if (i + 1 < multiplier) multiplied_string.append("?");
        }
        number_of_arrangements += get_number_of_arrangements(multiplied_string, multiplied_numbers);
    }
    return number_of_arrangements;
}

void solve(const std::vector<std::string>& lines) {
    std::cout << "1) Result is " << get_sum_of_arrangements(lines) << std::endl;
    std::cout << "2) Result is " << get_sum_of_arrangements(lines, 5) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day12"));
}