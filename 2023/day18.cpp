#include "day0.h"

std::size_t count_enclosed_tiles(auto& trenches_map) {
    std::size_t total{0};
    for (auto& [y, x_list] : trenches_map) {;
        std::sort(x_list.begin(), x_list.end());
        std::size_t last_x{x_list[0]};
        bool inside{false};
        for (auto& x : x_list) {
            if (trenches_map.contains(y - 1) && contains(trenches_map[y - 1], x)) {
                if (inside && x - last_x >= 1)
                    total += x - last_x - 1;
                inside = !inside;
                last_x = x;
            }
            else if (!inside) last_x = x;
            else last_x++;
        }
        total += x_list.size();
    }
    return total;
}

void dig(auto& trenches_map, char direction, std::size_t length, std::size_t& current_x, std::size_t& current_y) {
    int delta_x{direction == 'R' ? 1 : (direction == 'L' ? -1 : 0)};
    int delta_y{direction == 'D' ? 1 : (direction == 'U' ? -1 : 0)};
    trenches_map.reserve(length);
    while (length-- != 0) trenches_map[(current_y += delta_y)].push_back((current_x += delta_x));
}

void solve(const std::vector<std::string>& lines) {
    std::unordered_map<std::size_t, std::vector<std::size_t>> trenches_map{};
    std::size_t x{(1ul << 33) - 1}, y{(1ul << 33) - 1};
    for (auto& line : trim_lines(lines)) {
        const auto splits{split(line)};
        dig(trenches_map, splits[0][0], std::stoul(splits[1]), x, y);
    }
    std::cout << "1) Result is " << count_enclosed_tiles(trenches_map) << std::endl;

    trenches_map.clear();
    std::unordered_map<char, char> direction_translation{{'0', 'R'}, {'1', 'D'}, {'2', 'L'}, {'3', 'U'}};
    for (auto& line : trim_lines(lines)) {
        const auto hex_code{split(line)[2]};
        dig(trenches_map, direction_translation[hex_code[7]], std::stoul(hex_code.substr(2, 5), nullptr, 16), x, y);
    }
    std::cout << "2) Result is " << count_enclosed_tiles(trenches_map) << std::endl;
}

int main() {
    solve(read_input_file("../inputs/day18"));
}
