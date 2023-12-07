#include "../day0.h"

#define MAX_RED 12
#define MAX_BLUE 14
#define MAX_GREEN 13

std::vector<std::size_t> get_ordering(const std::string& str) {
    std::size_t r{str.find("red")}, b{str.find("blue")}, g{str.find("green")};
    return {0ul + (r >= b) + (r > g), 0ul + (b > r) + (b >= g), 0ul + (g >= r) + (g > b)};
}

void solve(const std::vector<std::string>& input) {
    std::size_t sum_of_game_ids{0};
    std::size_t power_of_cubes{0};
    std::for_each(input.begin(), input.end(), [&](const std::string& line) {
        if (line.empty())
            return;
        std::vector<std::string> splits{split(line, ':')};
        std::string game_id{split(splits[0])[1]};
        std::vector<std::string> draws{split(splits[1], ';')};
        std::size_t min_red_cubes{0}, min_blue_cubes{0}, min_green_cubes{0};
        bool is_possible_game{true};
        for (const std::string& draw : draws) {
            std::vector<std::size_t> ordering{get_ordering(draw)};
            std::vector<std::string> numbers{split(draw)};
            std::size_t red{0}, blue{0}, green{0};
            if (2 * ordering[0] < numbers.size())
                min_red_cubes = std::max(red = std::stoul(numbers[2 * ordering[0]]), min_red_cubes);
            if (2 * ordering[1] < numbers.size())
                min_blue_cubes = std::max(blue = std::stoul(numbers[2 * ordering[1]]), min_blue_cubes);
            if (2 * ordering[2] < numbers.size())
                min_green_cubes = std::max(green = std::stoul(numbers[2 * ordering[2]]), min_green_cubes);
            is_possible_game = is_possible_game && red <= MAX_RED && blue <= MAX_BLUE && green <= MAX_GREEN;
        }
        if (is_possible_game)
            sum_of_game_ids += std::stoi(game_id);
        power_of_cubes += min_red_cubes * min_blue_cubes * min_green_cubes;
    });
    std::cout << "1) Result is " << sum_of_game_ids << std::endl;
    std::cout << "2) Result is " << power_of_cubes << std::endl;
}

int main() {
    solve(read_input_file("../day02/day02_input"));
}