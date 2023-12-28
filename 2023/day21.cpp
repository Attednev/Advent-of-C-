#include "day0.h"

std::size_t hash(std::size_t x, std::size_t y) {
    return std::hash<std::string>{}(std::to_string(x) + ", " + std::to_string(y));
}

void walk(auto& lines, auto& next_visitor_counts, auto& identifier_to_position, auto x, auto y) {
    if (x >= lines[0].length() || y >= lines.size() || lines[y][x] != '.')
        return;
    next_visitor_counts[hash(x, y)] = true;
    identifier_to_position[hash(x, y)] = {x, y};
}

std::size_t get_number_of_gardens_small(auto& lines, std::size_t start_x, std::size_t start_y, std::size_t number_of_steps) {
    if (number_of_steps == range_index::npos) return 0;
    if (number_of_steps == 0) return 1;
    std::unordered_map<std::size_t, bool> visitor_counts{{hash(start_x, start_y), true}};
    std::unordered_map<std::size_t, std::pair<std::size_t, std::size_t>>identifier_to_position{{hash(start_x, start_y), std::make_pair(start_x, start_y)}};

    for (std::size_t step = 0; step < number_of_steps; step++) {
        std::unordered_map<std::size_t, bool> next_visitor_counts{};
        for (auto& [position, visitors] : visitor_counts) {
            auto [x, y] = identifier_to_position[position];
            if (lines[y][x] != '.') continue;
            walk(lines, next_visitor_counts, identifier_to_position, x - 1, y);
            walk(lines, next_visitor_counts, identifier_to_position, x + 1, y);
            walk(lines, next_visitor_counts, identifier_to_position, x, y - 1);
            walk(lines, next_visitor_counts, identifier_to_position, x, y + 1);
        }
        visitor_counts = std::move(next_visitor_counts);
    }
    return visitor_counts.size();
}

std::size_t get_number_of_gardens_small(auto& lines, auto starting_position, std::size_t number_of_steps) {
    return get_number_of_gardens_small(lines, starting_position.first, starting_position.second, number_of_steps);
}

std::size_t get_number_of_gardens_large(auto& lines, auto starting_position, std::size_t number_of_steps) {
    std::size_t distance{lines[0].length()};
    std::size_t half_distance{distance / 2};

    if (distance > number_of_steps)
        return get_number_of_gardens_small(lines, starting_position, number_of_steps);

    // Since all fields above, below and besides the starting point are dots, we can calculate, how often
    // the field gets copied in each direction.
    std::size_t number_of_grids{(std::size_t)(((double)(number_of_steps) - (double)half_distance) / (double)distance)};

    // Based on that information we can then calculate how many of those "grids" will be fully visited. Since the
    // markings of each tile in a fully visited grid alternates with each remaining step, we can also tell beforehand
    // which of the two results will be the right one.
    std::size_t result_type_1{get_number_of_gardens_small(lines, starting_position, 2 * distance)};
    std::size_t result_type_2{get_number_of_gardens_small(lines, starting_position, 2 * distance + 1)};

    // Which result a grid takes also alternates on each grid, which means that grids with the same result form a
    // diamond shape. We can simply take one of the diamonds base-length of the diamond and square it in order to
    // get the number of grids with the same outcome.
    std::size_t number_of_type_1{number_of_grids * number_of_grids};
    std::size_t number_of_type_2{(number_of_grids - 1) * (number_of_grids - 1)};

    // The grids at the outer border have to be calculated manually as we don't know how many steps are left
    std::size_t steps_remaining{number_of_steps - half_distance - (number_of_grids - 1) * distance - 1};

    //     1
    //    2-2
    //   23-32
    //  1-----1         grids denoted as '-' were already calculated as "full"
    //   23-32
    //    2-2
    //     1
    // We calculate the remainder at each end-point of the cardinal directions (1)
    std::size_t north{get_number_of_gardens_small(lines, half_distance, distance - 1, steps_remaining )};
    std::size_t east{get_number_of_gardens_small(lines, 0, half_distance, steps_remaining )};
    std::size_t south{get_number_of_gardens_small(lines, half_distance, 0, steps_remaining )};
    std::size_t west{get_number_of_gardens_small(lines, distance - 1, half_distance, steps_remaining)};

    // We calculate the inner grids of the border (3)
    std::size_t northeast{get_number_of_gardens_small(lines, distance - 1, distance - 1, half_distance + steps_remaining)};
    std::size_t northwest{get_number_of_gardens_small(lines, 0, distance - 1, half_distance + steps_remaining)};
    std::size_t southeast{get_number_of_gardens_small(lines, 0, 0, half_distance + steps_remaining)};
    std::size_t southwest{get_number_of_gardens_small(lines, distance - 1, 0, half_distance + steps_remaining)};

    // We calculate the outer grids of the border (2)
    std::size_t northeast_small{get_number_of_gardens_small(lines, distance - 1, distance - 1, half_distance - 1)};
    std::size_t northwest_small{get_number_of_gardens_small(lines, 0, distance - 1, half_distance - 1)};
    std::size_t southeast_small{get_number_of_gardens_small(lines, 0, 0, half_distance - 1)};
    std::size_t southwest_small{get_number_of_gardens_small(lines, distance - 1, 0, half_distance - 1)};

    return result_type_1 * number_of_type_1 + result_type_2 * number_of_type_2 + north + east + south + west
           + (number_of_grids - 1) * (northeast + northwest + southeast + southwest)
           + number_of_grids * (northeast_small + northwest_small + southeast_small + southwest_small);
}

void solve(const std::vector<std::string>& input) {
    auto lines{trim_lines(input)};
    std::pair<std::size_t, std::size_t> starting_position{lines[0].length() / 2, lines.size() / 2};
    lines[starting_position.second][starting_position.first] = '.';

    std::cout << "1) Result is " << get_number_of_gardens_small(lines, starting_position, 64) << std::endl;
    std:: cout << "2) Result is " << get_number_of_gardens_large(lines, starting_position, 26501365) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day21"));
}
