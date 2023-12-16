#include "day0.h"

std::size_t pop_front(std::deque<std::size_t>& deque) {
    std::size_t top{deque.front()};
    deque.pop_front();
    return top;
}

void tilt_vertical(std::vector<std::string>& lines, bool reverse_direction = false) {
    for (std::size_t x = 0; x < lines[0].length(); x++) {
        std::deque<std::size_t> empty_positions{};
        for (std::size_t y_itr = 0; y_itr < lines.size(); y_itr++) {
            std::size_t y{reverse_direction ? lines.size() - y_itr - 1 : y_itr};
            if (lines[y][x] == 'O' && !empty_positions.empty()) std::swap(lines[y][x], lines[pop_front(empty_positions)][x]);
            if (lines[y][x] == '.') empty_positions.push_back(y);
            if (lines[y][x] == '#') empty_positions.clear();
        }
    }
}

void tilt_horizontal(std::vector<std::string>& lines, bool reverse_direction = false) {
    for (std::size_t y = 0; y < lines.size(); y++) {
        std::deque<std::size_t> empty_positions{};
        for (std::size_t x_itr = 0; x_itr < lines[0].length(); x_itr++) {
            std::size_t x{reverse_direction ? lines.size() - x_itr - 1 : x_itr};
            if (lines[y][x] == 'O' && !empty_positions.empty()) std::swap(lines[y][x], lines[y][pop_front(empty_positions)]);
            if (lines[y][x] == '.') empty_positions.push_back(x);
            if (lines[y][x] == '#') empty_positions.clear();
        }
    }
}

void cycle(std::vector<std::string>& lines) {
    tilt_vertical(lines);
    tilt_horizontal(lines);
    tilt_vertical(lines, true);
    tilt_horizontal(lines, true);
}

std::size_t evaluate_position(const std::vector<std::string>& lines) {
    std::size_t total_load{0};
    for (std::size_t i = 0; i < lines.size(); i++)
        total_load += (lines.size() - i) * std::count_if(lines[i].begin(), lines[i].end(), [](auto c) { return c == 'O'; });
    return total_load;
}

std::size_t calculate_load(std::vector<std::string> lines, std::size_t number_of_cycles = 0) {
    if (number_of_cycles == 0) {
        tilt_vertical(lines);
        return evaluate_position(lines);
    }
    std::unordered_map<std::size_t, std::size_t> memoize{};
    for (std::size_t i = 0; i < number_of_cycles; i++) {
        std::size_t hash{std::hash<std::string>{}(join(lines, ""))};
        if (!memoize.contains(hash)) memoize.insert({hash, i});
        else i = number_of_cycles - ((number_of_cycles - i) % (i - memoize[hash]));
        cycle(lines);
    }
    return evaluate_position(lines);
}

void solve(const std::vector<std::string>& lines) {
    std::cout << "1) Result is " << calculate_load(trim_lines(lines)) << std::endl;
    std::cout << "2) Result is " << calculate_load(trim_lines(lines), 1'000'000'000) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day14"));
}