#include "day0.h"

enum direction { UP, LEFT, DOWN, RIGHT };

struct beam {
    std::size_t x, y;
    enum direction direction;
    beam(std::size_t i, std::size_t j, enum direction d) : x{i}, y{j}, direction{d} {}
};

direction reflect_beam(char tile, std::deque<beam>& beams, beam& current_beam) {
    // UP: 00, LEFT: 01, DOWN: 10, RIGHT: 11
    if (tile == '/')
        return static_cast<direction>(current_beam.direction ^ 0x3);   // 00 <-> 11, 01 <-> 10
    if (tile == '\\')
        return static_cast<direction>(current_beam.direction ^ 0x1);   // 00 <-> 01, 10 <-> 11
    if (tile == '|' && (current_beam.direction == LEFT || current_beam.direction == RIGHT)) {
        beams.emplace_back(current_beam.x, current_beam.y - 1, UP);
        return DOWN;
    }
    if (tile == '-' && (current_beam.direction == UP || current_beam.direction == DOWN)) {
        beams.emplace_back(current_beam.x - 1, current_beam.y, LEFT);
        return RIGHT;
    }
    return current_beam.direction;
}

void travel(beam& current_beam) {
    if (current_beam.direction == UP) current_beam.y--;
    else if (current_beam.direction == DOWN) current_beam.y++;
    else if (current_beam.direction == LEFT) current_beam.x--;
    else if (current_beam.direction == RIGHT) current_beam.x++;
}

std::size_t calculate_energy(const std::vector<std::string>& lines, const beam start_position = {0, 0, RIGHT}) {
    std::deque<beam> beams{start_position};
    std::size_t width{lines[0].length()};
    std::size_t total_size{lines.size() * width};
    std::vector<bool> visited(lines.size() * lines[0].length() * 4, false);
    while (!beams.empty()) {
        beam& current_beam{beams[0]};
        while (current_beam.x < lines[0].length() && current_beam.y < lines.size()) {
            std::size_t node_index{current_beam.y * width + current_beam.x + current_beam.direction * total_size};
            if (visited[node_index])
                break;
            visited[node_index] = true;
            current_beam.direction = reflect_beam(lines[current_beam.y][current_beam.x], beams, current_beam);
            travel(current_beam);
        }
        beams.pop_front();
    }
    std::size_t energy_level{0};
    for (std::size_t i = 0; i < total_size; i++)
        energy_level += visited[i] | visited[i + total_size] | visited[i + 2 * total_size] | visited[i + 3 * total_size];
    return energy_level;
}

std::size_t find_max_energy(const std::vector<std::string>& lines) {
    std::size_t max_energy{};
    for (std::size_t j = 0; j < lines[0].length(); j++) {
        max_energy = std::max(max_energy, calculate_energy(lines, {j, 0, DOWN}));
        max_energy = std::max(max_energy, calculate_energy(lines, {j, lines.size() - 1, UP}));
    }
    for (std::size_t j = 0; j < lines.size(); j++) {
        max_energy = std::max(max_energy, calculate_energy(lines, {0, j, RIGHT}));
        max_energy = std::max(max_energy, calculate_energy(lines, {lines[0].length() - 1, j, LEFT}));
    }
    return max_energy;
}

void solve(const std::vector<std::string>& lines) {
    std::cout << "1) Result is " << calculate_energy(lines) << std::endl;
    std::cout << "2) Result is " << find_max_energy(lines) << std::endl;
}

int main() {
    solve(trim_lines(read_input_file("../inputs/day16")));
}
