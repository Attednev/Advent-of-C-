#include "day0.h"
#include <chrono>
#include <thread>

enum direction { NORTH, EAST, SOUTH, WEST, NONE };


char get_start_replacement(direction start_direction, direction last_direction) {
    if (last_direction == start_direction && (last_direction == NORTH || last_direction == SOUTH)) // NN,SS: |
        return '|';
    if (last_direction == start_direction && (last_direction == EAST || last_direction == WEST)) // WW,OO: -
        return '-';
    if ((last_direction ^ start_direction) == 0x3 && (last_direction == NORTH || last_direction == EAST)) // NW,OS: 7
        return '7';
    if ((last_direction ^ start_direction) == 0x1 && (last_direction == NORTH || last_direction == WEST)) // NO,WS: F
        return 'F';
    if ((last_direction ^ start_direction) == 0x3 && (last_direction == SOUTH || last_direction == WEST)) // SO,WN: L
        return 'L';
    if ((last_direction ^ start_direction) == 0x1 && (last_direction == SOUTH || last_direction == EAST)) // SW,ON: J
        return 'J';
    return'S'; // No replacement found
}

char get_maze_map(const auto& lines, auto& map_of_maze, const auto& start_pos, auto pos, direction last_direction = NONE) {
    std::vector<char> north{'|', 'F', '7', 'S'}, east{'-', 'J', '7', 'S'}, south{'|', 'J', 'L', 'S'}, west{'-', 'L', 'F', 'S'};
    direction start_direction{NONE};
    while (last_direction == NONE || pos != start_pos) {
        if (last_direction != SOUTH && pos.first > 0 && contains(north, lines[pos.first - 1][pos.second]) && contains(south, lines[pos.first][pos.second])) {
            map_of_maze[pos.first--].emplace_back(pos.second);
            last_direction = NORTH;
        } else if (last_direction != WEST && pos.second < lines[0].length() - 1 && contains(east, lines[pos.first][pos.second + 1]) && contains(west, lines[pos.first][pos.second])) {
            map_of_maze[pos.first].emplace_back(pos.second++);
            last_direction = EAST;
        } else if (last_direction != NORTH && pos.first < lines.size() - 1 && contains(south, lines[pos.first + 1][pos.second]) && contains(north, lines[pos.first][pos.second])) {
            map_of_maze[pos.first++].emplace_back(pos.second);
            last_direction = SOUTH;
        } else if (last_direction != EAST && pos.second > 0 && contains(west, lines[pos.first][pos.second - 1]) && contains(east, lines[pos.first][pos.second])) {
            map_of_maze[pos.first].emplace_back(pos.second--);
            last_direction = WEST;
        }
        if (start_direction == NONE)
            start_direction = last_direction;
    }
    return get_start_replacement(start_direction, last_direction);
}

std::size_t get_number_of_enclosed_tiles(std::vector<std::string> lines, const auto& start_pos) {
    std::unordered_map<std::size_t, std::vector<std::size_t>> map_of_maze{};
    lines[start_pos.first][start_pos.second] = get_maze_map(lines, map_of_maze, start_pos, start_pos);
    std::size_t total{0};
    for (auto& [y, x_list] : map_of_maze) {
        std::sort(x_list.begin(), x_list.end());
        std::size_t last_x{x_list[0]};
        bool inside{false};
        for (auto& x : x_list) {
            if (contains({'J', '|', 'L'}, lines[y][x])) {
                if (inside)
                    total += x - last_x - 1;
                inside = !inside;
                last_x = x;
            }
            else if (!inside) last_x = x;
            else last_x++;
        }
    }
    return total;
}

std::size_t get_loop_length(const std::vector<std::string>& lines, auto& start_pos) {
    std::unordered_map<std::size_t, std::vector<std::size_t>> map_of_maze{};
    get_maze_map(lines, map_of_maze, start_pos, start_pos);
    std::size_t total{0};
    for (auto& [y, x_list] : map_of_maze)
        total += x_list.size();
    return total;
}

std::pair<std::size_t, std::size_t> find_starting_position(const std::vector<std::string>& lines) {
    for (std::size_t i = 0; i < lines.size(); i++)
        for (std::size_t j = 0; j < lines[0].length(); j++)
            if (lines[i][j] == 'S')
                return {i, j};
    return {range_index::npos, range_index::npos};
}

void solve(const std::vector<std::string>& lines) {
    auto starting_position{find_starting_position(lines)};
    std::cout << "1) Result is " << (get_loop_length(lines, starting_position) + 1) / 2 << std::endl;
    std::cout << "2) Result is " << get_number_of_enclosed_tiles(lines, starting_position) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day10"));
}
