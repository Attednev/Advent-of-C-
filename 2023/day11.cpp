#include "day0.h"

std::size_t calculate_distance(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2) {
    return (std::max(x1, x2) - std::min(x1, x2)) + (std::max(y1, y2) - std::min(y1, y2));
}

std::vector<std::size_t> get_empty_columns(const std::vector<std::string>& lines) {
    std::vector<std::size_t> empty_columns{};
    for (std::size_t i = 0; i < lines[0].length(); i++) {
        bool is_column_empty{true};
        for (const auto& line : lines)
            if (line[i] != '.' && line[i] != '\r')
                is_column_empty = false;
        if (is_column_empty)
            empty_columns.push_back(i);
    }
    return empty_columns;
}

std::vector<std::size_t> get_empty_rows(const std::vector<std::string>& lines) {
    std::vector<std::size_t> empty_rows{};
    for (std::size_t i = 0; i < lines.size(); i++) {
        bool is_row_empty{true};
        for (const auto& symbol : trim(lines[i]))
            if (symbol != '.')
                is_row_empty = false;
        if (is_row_empty)
            empty_rows.push_back(i);
    }
    return empty_rows;
}

std::unordered_map<std::size_t, std::vector<std::size_t>> get_universe_map(const std::vector<std::string>& lines, std::size_t empty_replacement) {
    std::unordered_map<std::size_t, std::vector<std::size_t>> map{};
    std::size_t current_y{0};
    std::vector<std::size_t> empty_rows{get_empty_rows(lines)}, &&empty_columns{get_empty_columns(lines)};
    for (std::size_t i = 0; i < lines.size(); i++, current_y++) {
        if (contains(empty_rows, i)) {
            current_y += empty_replacement - 1;
            continue;
        }
        std::size_t added_columns{0};
        std::string trimmed{trim(lines[i])};
        for (std::size_t j = 0; j < trimmed.length(); j++) {
            if (contains(empty_columns, j)) {
                added_columns += empty_replacement - 1;
                continue;
            }
            if (trimmed[j] != '.' && trimmed[j] != '\r')
                insert_or_append(map, current_y, j + added_columns);
        }
    }
    return map;
}

std::size_t calculate_total_distance(const std::vector<std::string>& lines, std::size_t empty_replacement) {
    std::unordered_map<std::size_t, std::vector<std::size_t>> map_of_universe{get_universe_map(lines, empty_replacement)};
    std::size_t total_distance{0};
    for (auto [y1, x1_loc] : map_of_universe)
        for (auto x1 : x1_loc)
            for (auto [y2, x2_loc]: map_of_universe)
                for (auto x2 : x2_loc)
                    total_distance += calculate_distance(x1, y1, x2, y2);
    return total_distance;
}

void solve(const std::vector<std::string>& lines) {
    std::cout << "1) Result is " << (calculate_total_distance(lines, 2)) / 2 << std::endl;
    std::cout << "2) Result is " << (calculate_total_distance(lines, 1000000)) / 2 << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day11"));
}
