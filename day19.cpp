#include "day0.h"

#define PARSING_STATE 0
#define READING_OPERATIONS 0
#define READING_CONFIGURATIONS 1
#define READING_EOF 2

struct operation {
    char variable{' '};
    char operation{' '};
    std::size_t constant{0};
    std::string target;
};

struct part_state {
    std::size_t x;
    std::size_t m;
    std::size_t a;
    std::size_t s;
};

struct range {
    std::size_t x_start;
    std::size_t x_end;
    std::size_t m_start;
    std::size_t m_end;
    std::size_t a_start;
    std::size_t a_end;
    std::size_t s_start;
    std::size_t s_end;
};

void parse_input(const auto& lines, auto& states, auto& operations) {
    auto parsing_state{READING_OPERATIONS};
    for (auto& line : trim_lines(lines)) {
        if (line.empty()) {
            if (++parsing_state == READING_EOF)
                break;
            continue;
        }
        if (parsing_state == READING_CONFIGURATIONS) {
            auto splits{split(line.substr(1, line.length() - 2), ',')};
            states.emplace_back(std::stoul(splits[0].substr(2)), std::stoul(splits[1].substr(2)),
                                std::stoul(splits[2].substr(2)), std::stoul(splits[3].substr(2)));
            continue;
        }
        auto splits{split(line, '{')};
        for (auto op : split(splits[1].substr(0, splits[1].length() - 1), ',')) {
            auto number_split{split(op, ':')};
            if (number_split.size() == 1) {
                operations[splits[0]].emplace_back(' ', '+', 0, op);
                continue;
            }
            auto constant{number_split[0].substr(2)};
            operations[splits[0]].emplace_back(op[0], op[1], std::stoul(constant), number_split[1]);
        }
    }
}

auto update_range(range& ranges, char v, char o, std::size_t c) {
    range next_range{v == 'x' && o == '>' ? c + 1 : ranges.x_start, v == 'x' && o == '<' ? c - 1 : ranges.x_end,
                     v == 'm' && o == '>' ? c + 1 : ranges.m_start, v == 'm' && o == '<' ? c - 1 : ranges.m_end,
                     v == 'a' && o == '>' ? c + 1 : ranges.a_start, v == 'a' && o == '<' ? c - 1 : ranges.a_end,
                     v == 's' && o == '>' ? c + 1 : ranges.s_start, v == 's' && o == '<' ? c - 1 : ranges.s_end};
    ranges = {ranges.x_start = v == 'x' && o == '<' ? c : ranges.x_start, ranges.x_end = v == 'x' && o == '>' ? c : ranges.x_end,
              ranges.m_start = v == 'm' && o == '<' ? c : ranges.m_start, ranges.m_end = v == 'm' && o == '>' ? c : ranges.m_end,
              ranges.a_start = v == 'a' && o == '<' ? c : ranges.a_start, ranges.a_end = v == 'a' && o == '>' ? c : ranges.a_end,
              ranges.s_start = v == 's' && o == '<' ? c : ranges.s_start, ranges.s_end = v == 's' && o == '>' ? c : ranges.s_end};
    return next_range;
}

std::size_t calculate_combinations(range& ranges) {
    return (ranges.x_end - ranges.x_start + 1) * (ranges.m_end - ranges.m_start + 1) * (ranges.a_end - ranges.a_start + 1) * (ranges.s_end - ranges.s_start + 1);
}

void is_part_accepted_part2(auto& operations, const std::string& current_workflow, range ranges, std::size_t& result) {
    if (current_workflow == "A")
        return (void)(result += calculate_combinations(ranges));
    if (current_workflow == "R" || !operations.contains(current_workflow))
        return;
    for (auto& [v, o, c, t] : operations[current_workflow])
        is_part_accepted_part2(operations, t, update_range(ranges, v, o, c),result);
}

bool is_part_accepted_part1(const auto& operations, const auto& part, const std::string& current_workflow) {
    if (current_workflow == "A")
        return true;
    if (current_workflow == "R" || !operations.contains(current_workflow))
        return false;
    for (auto& [v, o, c, t] : operations.at(current_workflow)) {
        std::size_t target_variable{v == 'x' ? part.x : (v == 'm' ? part.m : (v == 'a' ? part.a : part.s))};
        if (o == '+' || (o == '<' && target_variable < c) || (o == '>' && target_variable > c))
            return is_part_accepted_part1(operations, part, t);
    }
    return false;
}

void solve(const std::vector<std::string>& lines) {
    std::vector<part_state> states{};
    std::unordered_map<std::string, std::vector<operation>> operations{};
    parse_input(lines, states, operations);

    std::size_t total{0};
    for (auto part : states) {
        auto& [x, m, a, s] = part;
        if (is_part_accepted_part1(operations, part, "in"))
            total += x + m + a + s;
    }
    std::cout << "1) Result is " << total << std::endl;

    std::size_t result{0};
    std::vector<range> ranges_list{};
    is_part_accepted_part2(operations, "in", {1, 4000, 1, 4000, 1, 4000, 1, 4000}, result);
    std::cout << "2) Result is " << result << std::endl;
}

int main(int argc, char** argv) {
    solve(read_input_file("day19_real"));
}
