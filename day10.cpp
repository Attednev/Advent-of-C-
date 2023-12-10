#include "day0.h"

enum direction { NORTH, EAST, SOUTH, WEST, NONE };

struct position {
    std::size_t i{range_index::npos}, j{range_index::npos};
    direction d{NONE};
    bool operator==(const position& other) const { return i == other.i && j == other.j; }
    bool operator>=(const position& other) const { return i >= other.i || j >= other.j; }
};

#define pos_vec std::vector<position>

bool get_maze_map(const std::vector<std::string>& lines, pos_vec& map_of_maze, const position start_pos, const position pos, const direction last_direction = NONE) {
    if (last_direction != NONE && pos == start_pos)
        return true;

    std::vector<char> north{'|', 'F', '7', 'S'}, east{'-', 'J', '7', 'S'}, south{'|', 'J', 'L', 'S'}, west{'-', 'L', 'F', 'S'};
    if (last_direction != SOUTH && pos.i > 0 && contains(north, lines[pos.i - 1][pos.j]) && contains(south, lines[pos.i][pos.j])
        && get_maze_map(lines, map_of_maze, start_pos, {pos.i - 1, pos.j}, NORTH)) {
        map_of_maze.emplace_back(pos.i, pos.j, NORTH);
        return true;
    }
    if (last_direction != WEST && pos.j < lines[0].length() - 1 && contains(east, lines[pos.i][pos.j + 1]) && contains(west, lines[pos.i][pos.j])
        && get_maze_map(lines, map_of_maze, start_pos, {pos.i, pos.j + 1}, EAST)) {
        map_of_maze.emplace_back(pos.i, pos.j, EAST);
        return true;
    }
    if (last_direction != NORTH && pos.i < lines.size() - 1 && contains(south, lines[pos.i + 1][pos.j]) && contains(north, lines[pos.i][pos.j])
        && get_maze_map(lines, map_of_maze, start_pos, {pos.i + 1, pos.j}, SOUTH)) {
        map_of_maze.emplace_back(pos.i, pos.j, SOUTH);
        return true;
    }
    if (last_direction != EAST && pos.j > 0 && contains(west, lines[pos.i][pos.j - 1]) && contains(east, lines[pos.i][pos.j])
        && get_maze_map(lines, map_of_maze, start_pos, {pos.i, pos.j - 1}, WEST)) {
        map_of_maze.emplace_back(pos.i, pos.j, WEST);
        return true;
    }

    return false;
}

void fill_enclosed_tiles(pos_vec& map_of_maze, std::vector<short>& visited, position pos, position boundaries) {
    if (pos >= boundaries || contains(map_of_maze, pos) || visited[pos.i * boundaries.j + pos.j] > 0)
        return;
    visited[pos.i * boundaries.j + pos.j]++;
    fill_enclosed_tiles(map_of_maze, visited, {pos.i, pos.j + 1}, boundaries);
    fill_enclosed_tiles(map_of_maze, visited, {pos.i + 1, pos.j}, boundaries);
}

std::size_t get_number_of_enclosed_tiles(const std::vector<std::string>& lines, position start_pos) {
    direction last_direction{NONE};
    pos_vec map_of_maze{}, enclosed_nodes{};
    get_maze_map(lines, map_of_maze, start_pos, start_pos);
    std::vector<short> visited(lines.size() * lines[0].length(), 0);
    for (auto& [i, j, d] : map_of_maze) {
        position neighbour{d == NORTH || d == SOUTH ? i : i + 2 - d, d == EAST || d == WEST ? j : j + 1 - d};
        //position neighbour{d == NORTH || d == SOUTH ? i : i - 2 + d, d == EAST || d == WEST ? j : j - 1 + d};
        fill_enclosed_tiles(map_of_maze, visited, neighbour, {lines.size(), lines[0].length()});
        if (d != last_direction) {
            neighbour = {d == NORTH || d == WEST ? i - 1 : i + 1, d == NORTH || d == EAST ? j + 1 : j - 1};
            //neighbour = {d == NORTH || d == WEST ? i + 1 : i - 1, d == NORTH || d == EAST ? j - 1 : j + 1};
            fill_enclosed_tiles(map_of_maze, visited, neighbour, {lines.size(), lines[0].length()});
        }
    }
    return std::count_if(visited.begin(), visited.end(), [](auto element) { return element > 0; });
}

std::size_t get_loop_length(const std::vector<std::string>& lines, position start_pos) {
    pos_vec map_of_maze{};
    get_maze_map(lines, map_of_maze, start_pos, start_pos);
    return map_of_maze.size();
}

position find_starting_position(const std::vector<std::string>& lines) {
    for (std::size_t i = 0; i < lines.size(); i++)
        for (std::size_t j = 0; j < lines[0].length(); j++)
            if (lines[i][j] == 'S')
                return {i, j};
    return {range_index::npos, range_index::npos};
}

void solve(const std::vector<std::string>& lines) {
    position starting_position{find_starting_position(lines)};
    std::cout << "1) Result is " << (get_loop_length(lines, starting_position) + 1) / 2 << std::endl;
    std::cout << "2) Result is " << get_number_of_enclosed_tiles(lines, starting_position) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day10"));
}
